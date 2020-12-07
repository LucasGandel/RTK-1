/*=========================================================================
 *
 *  Copyright RTK Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#define ITK_TEMPLATE_EXPLICIT_ConstantImageSource
#include "rtkConstantImageSource.h"

namespace rtk
{

ITK_GCC_PRAGMA_DIAG_PUSH()
ITK_GCC_PRAGMA_DIAG(ignored "-Wattributes")

template class RTK_EXPORT ConstantImageSource<itk::CudaImage<float, 3>>;
template class RTK_EXPORT ConstantImageSource<itk::CudaImage<float, 4>>;
template class RTK_EXPORT ConstantImageSource<itk::CudaImage<itk::CovariantVector<float, 3>, 3>>; // needed for itk::CudaImage<itk::CovariantVector<float, 3>, 3> in rtkADMMTotalVariationTest

ITK_GCC_PRAGMA_DIAG_POP()
} // namespace rtk