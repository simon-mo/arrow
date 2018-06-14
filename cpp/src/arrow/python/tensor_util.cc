// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "arrow/python/tensor_util.h"

#include "arrow/io/memory.h"
#include "arrow/python/python_to_arrow.h"

namespace arrow {

namespace py {

Status TensorFlowTensorGetHeaderSize(std::shared_ptr<arrow::DataType> dtype,
                                     const std::vector<int64_t>& shape,
                                     int64_t* header_size) {
  arrow::io::MockOutputStream mock;
  auto empty_tensor = std::make_shared<arrow::Tensor>(dtype, std::make_shared<arrow::Buffer>(nullptr, 0), shape);
  arrow::py::SerializedPyObject serialized_tensor;
  RETURN_NOT_OK(SerializeTensor(empty_tensor, &serialized_tensor));
  RETURN_NOT_OK(serialized_tensor.WriteTo(&mock));
  *header_size = mock.GetExtentBytesWritten();
  return Status::OK();
}

Status TensorFlowTensorWrite(std::shared_ptr<arrow::DataType> dtype,
                             const std::vector<int64_t>& shape,
                             std::shared_ptr<Buffer> buffer, int64_t* offset) {
  arrow::io::FixedSizeBufferWriter buf(buffer);
  auto empty_tensor = std::make_shared<arrow::Tensor>(dtype, std::make_shared<arrow::Buffer>(nullptr, 0), shape);
  arrow::py::SerializedPyObject serialized_tensor;
  RETURN_NOT_OK(SerializeTensor(empty_tensor, &serialized_tensor));
  RETURN_NOT_OK(serialized_tensor.WriteTo(&buf));
  return buf.Tell(offset);
}

}  // namespace py

}  // namespace arrow