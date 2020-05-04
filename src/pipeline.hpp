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
#ifndef PIPELINE_HPP
#define PIPELINE_HPP


#include "pipeline/data.hpp"
#include "pipeline/process.hpp"

// #include <cassert>
// #include <iostream>
// #include <memory>
// #include <stdexcept>
// #include <tuple>
// #include <type_traits>


struct image : public pipeline::data
{
  void set_information( int ) {}
  int information() const { return -1; }
};


struct image_file_reader : public pipeline::reader< image >
{
private:
  void
  generate_output_information() override
  {
    std::cout << "image_file_reader::generate_output_information()" << std::endl;
  }
};


struct image_file_writer : public pipeline::writer< image >
{
};


struct ndvi_filter : public pipeline::process< pipeline::input< image >,
					       pipeline::output< image > >
{
};


struct point_cloud : public pipeline::data
{
  void set_information( int ) {}
  int information() const { return -1; }
};


struct las_file_reader : public pipeline::reader< point_cloud >
{
  void
  generate_output_information() override
  {
    std::cout << "las_file_reader::generate_output_information()" << std::endl;
  }
};


struct las_file_writer : public pipeline::writer< point_cloud >
{
};


struct point_cloud_algorithm : public pipeline::process< pipeline::input< point_cloud >,
							 pipeline::output< point_cloud > >
{
};


#endif // PIPELINE_HPP
