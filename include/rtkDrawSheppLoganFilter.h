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

#ifndef rtkDrawSheppLoganFilter_h
#define rtkDrawSheppLoganFilter_h

#include "rtkDrawGeometricPhantomImageFilter.h"

#ifdef RTK_USE_CUDA
#  include "itkCudaImage.h"
#endif

namespace rtk
{

/** \class DrawSheppLoganFilter
 * \brief Draws a SheppLoganPhantom in a 3D image with a default scale of 128.
 *
 * \test rtkRaycastInterpolatorForwardProjectionTest.cxx,
 * rtkProjectGeometricPhantomTest.cxx, rtkfdktest.cxx, rtkRampFilterTest.cxx,
 * rtkForwardProjectionTest.cxx, rtkdisplaceddetectortest.cxx,
 * rtkShortScanTest.cxx, rtkforbildtest.cxx
 *
 * \author Marc Vila, Simon Rit
 *
 * \ingroup RTK InPlaceImageFilter
 */
template <class TInputImage, class TOutputImage>
class ITK_TEMPLATE_EXPORT DrawSheppLoganFilter : public DrawGeometricPhantomImageFilter<TInputImage, TOutputImage>
{
public:
#if ITK_VERSION_MAJOR == 5 && ITK_VERSION_MINOR == 1
  ITK_DISALLOW_COPY_AND_ASSIGN(DrawSheppLoganFilter);
#else
  ITK_DISALLOW_COPY_AND_MOVE(DrawSheppLoganFilter);
#endif

  /** Standard class type alias. */
  using Self = DrawSheppLoganFilter;
  using Superclass = DrawGeometricPhantomImageFilter<TInputImage, TOutputImage>;
  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(DrawSheppLoganFilter, DrawGeometricPhantomImageFilter);

protected:
  DrawSheppLoganFilter();
  ~DrawSheppLoganFilter() override = default;

  void
  GenerateData() override;
};

} // end namespace rtk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "rtkDrawSheppLoganFilter.hxx"
#endif

#endif


/** Explicit instantiations */
#if defined(RTK_USE_CUDA) && !defined(ITK_TEMPLATE_EXPLICIT_DrawSheppLoganFilter)
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

extern template class RTK_EXPORT_EXPLICIT DrawSheppLoganFilter<itk::CudaImage<float, 3>, itk::CudaImage<float, 3>>;

ITK_GCC_PRAGMA_DIAG_POP()

} // end namespace rtk
#undef RTK_EXPORT_EXPLICIT
#endif
