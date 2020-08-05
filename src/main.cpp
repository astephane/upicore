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

#include "utility/pod.hpp"


#define unused( x )


void
image_pipeline()
{
  // using ifr_ptr_type = std::shared_ptr< image_file_reader >;
  // using ifw_otr_type = std::shared_ptr< image_file_writer >;

  image_file_reader ifr;
  image_file_writer ifw;
  ndvi_filter ndvi;

  ifw.in.get< 0 >() = ndvi.out.get< 0 >();
  ifw.in.get< 1 >() = ndvi.out.get< 1 >();

  ndvi.in.get< 0 >() = ifr.out.get< 0 >();
  ndvi.in.get< 1 >() = ifr.out.get< 1 >();

#if 0
  pipeline::process_interface * process = &ifw;

  process->update_output_info();

#else
  ifw.update_output_info();

#endif
}


void
point_cloud_pipeline()
{
  las_file_reader lfr;
  las_file_writer lfw;
  point_cloud_algorithm pca;

  lfw.in.get< 0 >() = pca.out.get< 0 >();
  lfw.in.get< 1 >() = pca.out.get< 1 >();

  pca.in.get< 0 >() = lfr.out.get< 0 >();
  pca.in.get< 1 >() = lfr.out.get< 1 >();

#if 0
  pipeline::process_interface * process = &lfw;

  process->update_output_info();

#else
  std::cout << std::endl << "Querying information..." << std::endl;
  lfw.update_output_info();

  std::cout << std::endl << "Processing data..." << std::endl;
  lfw.update_output_data();

  std::cout << std::endl << "DONE." << std::endl;
#endif
}


int
main( int unused( argc ), char * unused( argv )[] )
{
  // image_pipeline();
  point_cloud_pipeline();

  {
    using vector_type = utility::pod< sample_pod::vector, sample_pod::vector_traits >;

    vector_type v;

    std::cout << v.get< sample_pod::vector::x >() << std::endl;
  }

  return EXIT_SUCCESS;
}
