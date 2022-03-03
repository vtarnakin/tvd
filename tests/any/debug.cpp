﻿#include <iostream>
#include <mtl/numeric/sparse.hpp>

int main()
{ try {
	  using matrix_t = mtl::numeric::matrix_t<std::ptrdiff_t>;
	  matrix_t m
	  { 0, 1, 2, 3, 4, 0, 0, 1, 2 };
	  m.resize( 3 );
	  decltype( m ) m_( m );
	  mtl::numeric::vector_t<std::ptrdiff_t> v( m[0] );
	  std::cout << v;
	  std::cout << static_cast<decltype(v)>(m_[0]);
	  m_[0] += v;
	  m_[0] += m[0];
	  std::cout << m_;
  } catch( std::exception const& e ) {
	  std::cout << e.what() << std::endl;
  }
  system( "pause" );
  return 0;
}
