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


struct foo : public pipeline::data
{
  void set_info( int )
  {
    TRACE_THIS_FUN();
  }

  int info() const { return -1; }
};


struct image : public pipeline::data
{
  void set_info( int )
  {
    TRACE_THIS_FUN();
  }

  int info() const { return -1; }
};


struct image_file_reader : public pipeline::reader< image, foo >
{
private:
  void
  generate_output_info() override
  {
    TRACE_THIS_FUN();
  }

  void
  generate_output_data() override
  {
    TRACE_THIS_FUN();
  }
};


struct image_file_writer : public pipeline::writer< image, foo >
{
};


struct ndvi_filter : public pipeline::process< pipeline::input< image, foo >,
					       pipeline::output< image, foo > >
{
};


struct point_cloud : public pipeline::data
{
  void set_info( int )
  {
    TRACE_THIS_FUN();
  }

  int info() const { return -1; }
};


struct las_file_reader : public pipeline::reader< point_cloud, foo >
{
  void
  generate_output_info() override
  {
    TRACE_THIS_FUN();
  }

  void
  generate_output_data() override
  {
    TRACE_THIS_FUN();
  }
};


struct las_file_writer : public pipeline::writer< point_cloud, foo >
{
};


struct point_cloud_algorithm : public pipeline::process< pipeline::input< point_cloud, foo >,
							 pipeline::output< point_cloud, foo > >
{
};


#endif // PIPELINE_HPP
