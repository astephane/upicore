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

int
main( int unused( argc ), char * unused( argv )[] )
{
    // using ifr_ptr_type = std::shared_ptr< image_file_reader >;
    // using ifw_otr_type = std::shared_ptr< image_file_writer >;

    std::shared_ptr< image_file_reader > ifr;
    std::shared_ptr< image_file_writer > ifw;
    std::shared_ptr< ndvi_filter > ndvi;

    std::get< 0 >( ifw->in ).source = ndvi;
    std::get< 0 >( ndvi->in ).source = ifr;

    return EXIT_SUCCESS;
}
