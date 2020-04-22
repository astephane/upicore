//
// This file is part of upicore.
//
// upicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// upicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with upicore.  If not, see <https://www.gnu.org/licenses/>.
//

#include <cstdlib>


#include "pipeline.hpp"


#define unused( x )


void
image_pipeline()
{
  // using ifr_ptr_type = std::shared_ptr< image_file_reader >;
  // using ifw_otr_type = std::shared_ptr< image_file_writer >;

  image_file_reader ifr;
  image_file_writer ifw;
  ndvi_filter ndvi;

  ifw.input< 0 >() = &ndvi.output< 0 >();
  ndvi.input< 0 >() = &ifr.output< 0 >();
}


void
point_cloud_pipeline()
{
  las_file_reader lfr;
  las_file_writer lfw;
  point_cloud_algorithm pca;

  lfw.input< 0 >() = &pca.output< 0 >();
  pca.input< 0 >() = &lfr.output< 0 >();
}


int
main( int unused( argc ), char * unused( argv )[] )
{

  return EXIT_SUCCESS;
}
