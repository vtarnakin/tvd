#pragma once
#ifndef MTL_ABSTRACT_FACTORY_HPP
#define MTL_ABSTRACT_FACTORY_HPP

#include "exception.hpp"
#include "types.hpp"

#include <unordered_map>
#include <functional>

namespace mtl {

template<
    typename _KeyTy,
    typename ... _ArgsTy>
    class abstract_factory
    {
public :
      using key_t       = _KeyTy;
      using var_t       = detail::variant_t<std::shared_ptr<_ArgsTy> ... >;
      using o_var_t     = detail::optional_t<var_t>;
      using creator_t   = std::function<var_t()>;
      using creators_t  = std::unordered_map<key_t, creator_t>;
      using init_list_t = std::initializer_list< std::pair<key_t, creator_t> > const&;
private :
      creators_t creators_;
public :
      abstract_factory() = default;
      abstract_factory(abstract_factory const&) = default;
      abstract_factory& operator = (abstract_factory const&) = default;

      abstract_factory( init_list_t list ) 
      {
        for( auto const& pair : list )
            creators_.emplace( pair );
      }

      void register_class( key_t const& by_key, creator_t const& creator ) 
      {
        if( !creator ) {
            throw detail::exception_t( "<abstract_factory::register_class> : <creator> is empty wrap of functional object" );
        }
        if( creators_.find( by_key ) != creators_.end() ) {
            throw detail::exception_t( "<abstract_factory::register_class> : <by_key> already exsist" );
        }
        creators_[by_key] = creator;
      }

  template<class _ObjTy>
      void register_class( key_t const& by_key ) 
      {
        if( creators_.find( by_key ) != creators_.end() ) {
            throw detail::exception_t( "<abstract_factory::register_class> : <by_key> already exsist" );
        }
        creators_[by_key] = &creator<_ObjTy>;
      }

      o_var_t creat( key_t const& by_key ) 
      {
        auto it = creators_.find( by_key );
        return it != creators_.end() ? it->second() : MTL_NULLOPT;
      }
private :

  template<class _ObjTy>
      static var_t creator() 
      { return std::make_shared<_ObjTy>(); } 
    };
} // mtl
#endif
