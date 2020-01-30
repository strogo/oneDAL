/** file low_order_moments_online.cpp */
/*******************************************************************************
* Copyright 2019-2020 Intel Corporation
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

#include "fixture.hpp"

#include "low_order_moments_params.hpp"

namespace dalbench {
namespace low_order_moments {

namespace daal_low_order_moments = daal::algorithms::low_order_moments;

template <typename DeviceType, typename FPType>
class MomentsOnline : public GetterParamsMoments<FPType>,
                      public FixtureOnline<daal_low_order_moments::Online<FPType>, DeviceType> {
public:
  using AlgorithmType = typename daal_low_order_moments::Online<FPType>;
  using GetterParamsMoments<FPType>::params;

  MomentsOnline(const std::string& name,
                const typename GetterParamsMoments<FPType>::Params& params_in)
      : GetterParamsMoments<FPType>(params_in),
        FixtureOnline<AlgorithmType, DeviceType>(name, params) {}

protected:
  void set_algorithm() final {
    this->algorithm_ = std::make_unique<AlgorithmType>(AlgorithmType());
  }

  void set_input_block(benchmark::State& state, const size_t block_index) final {
    auto x_block = params.dataset.full().x_block(block_index);
    this->algorithm_->input.set(daal_low_order_moments::data, x_block);
  }
};

DAL_BENCH_REGISTER(MomentsOnline, CpuDevice, float);
DAL_BENCH_REGISTER(MomentsOnline, CpuDevice, double);

#if defined(DPCPP_INTERFACES) && (__INTEL_DAAL_BUILD_DATE >= ONEDAL_VERSION_2021_BETA_03_UPDATE)
DAL_BENCH_REGISTER(MomentsOnline, GpuDevice, float);
DAL_BENCH_REGISTER(MomentsOnline, GpuDevice, double);
#endif // defined(DPCPP_INTERFACES) && (__INTEL_DAAL_BUILD_DATE >= ONEDAL_VERSION_2021_BETA_03_UPDATE)

} // namespace low_order_moments
} // namespace dalbench
