/** file low_order_moments_params.hpp */
/*******************************************************************************
* Copyright 2020 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef DALBENCH_LOW_ORDER_MOMENTS_PARAMS_HPP_
#define DALBENCH_LOW_ORDER_MOMENTS_PARAMS_HPP_

#include "fixture.hpp"

namespace dalbench {

template <typename FPType>
class GetterParamsMoments {
public:
  struct Params : public CommonAlgorithmParams {
    Params(const DatasetName& dataset_name, const NumericTableType numeric_table_type)
        : CommonAlgorithmParams(dataset_name, numeric_table_type) {}
  };
  GetterParamsMoments(const Params& params) : params(params) {}

  static DictionaryParams<Params> get_params() {
    return { { "Higgs:2M", Params(DatasetName("higgs_2M"), TableType(SyclHomogen, FPType)) },
             { "Epsilon:80K",
               Params(DatasetName("epsilon_80k"), TableType(SyclHomogen, FPType)) } };
  }

  Params params;
};

} // namespace dalbench

#endif // DALBENCH_LOW_ORDER_MOMENTS_PARAMS_HPP_