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

#ifndef rtkForwardProjectionImageFilter_h
#define rtkForwardProjectionImageFilter_h

#include <itkInPlaceImageFilter.h>
#include "rtkThreeDCircularProjectionGeometry.h"
#include "rtkMacro.h"

#ifdef RTK_USE_CUDA
#  include "itkCudaImage.h"
#endif


namespace rtk
{

/** \class ForwardProjectionImageFilter
 * \brief Base class for forward projection, i.e. accumulation along x-ray lines.
 *
 * \author Simon Rit
 *
 * \ingroup RTK Projector
 */
template <class TInputImage, class TOutputImage = TInputImage>
class ForwardProjectionImageFilter : public itk::InPlaceImageFilter<TInputImage, TOutputImage>
{
public:
#if ITK_VERSION_MAJOR == 5 && ITK_VERSION_MINOR == 1
  ITK_DISALLOW_COPY_AND_ASSIGN(ForwardProjectionImageFilter);
#else
  ITK_DISALLOW_COPY_AND_MOVE(ForwardProjectionImageFilter);
#endif

  /** Standard class type alias. */
  using Self = ForwardProjectionImageFilter;
  using Superclass = itk::InPlaceImageFilter<TInputImage, TOutputImage>;
  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;

  using GeometryType = rtk::ThreeDCircularProjectionGeometry;
  using GeometryPointer = typename GeometryType::ConstPointer;

  /** Run-time type information (and related methods). */
  itkTypeMacro(ForwardProjectionImageFilter, itk::InPlaceImageFilter);

  /** Get / Set the object pointer to projection geometry */
  itkGetConstObjectMacro(Geometry, GeometryType);
  itkSetConstObjectMacro(Geometry, GeometryType);

protected:
  ForwardProjectionImageFilter()
    : m_Geometry(nullptr)
  {
    this->SetNumberOfRequiredInputs(2);
    this->SetInPlace(true);
  };

  ~ForwardProjectionImageFilter() override = default;

  /** Checks that inputs are correctly set. */
  void
  VerifyPreconditions() ITKv5_CONST override;

  /** Apply changes to the input image requested region. */
  void
  GenerateInputRequestedRegion() override;

  /** The two inputs should not be in the same space so there is nothing
   * to verify. */
  void
  VerifyInputInformation() const override
  {}

private:
  /** RTK geometry object */
  GeometryPointer m_Geometry;
};

} // end namespace rtk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "rtkForwardProjectionImageFilter.hxx"
#endif

#endif


/** Explicit instantiations */
#if defined(RTK_USE_CUDA) && !defined(ITK_TEMPLATE_EXPLICIT_ForwardProjectionImageFilter)
// Explicit instantiation is required to avoid multiple definitions
// across shared libraries.
//
// IMPORTANT: Since within the same compilation unit,
//            ITK_TEMPLATE_EXPLICIT_<classname> defined and undefined states
//            need to be considered. This code *MUST* be *OUTSIDE* the header
//            guards.
//
#if defined(RTK_EXPORTS)
//   We are building this library
#  define RTK_EXPORT_EXPLICIT ITK_TEMPLATE_EXPORT
#else
//   We are using this library
#  define RTK_EXPORT_EXPLICIT RTK_EXPORT
#endif

namespace rtk
{

  ITK_GCC_PRAGMA_DIAG_PUSH()
    ITK_GCC_PRAGMA_DIAG(ignored "-Wattributes")

    extern template class RTK_EXPORT_EXPLICIT ForwardProjectionImageFilter<itk::CudaImage<float, 3>, itk::CudaImage<float, 3>>;

  ITK_GCC_PRAGMA_DIAG_POP()

} // end namespace rtk
#undef RTK_EXPORT_EXPLICIT
#endif
