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

#ifndef rtkConstantImageSource_h
#define rtkConstantImageSource_h

#include "rtkConfiguration.h"
#include "rtkMacro.h"

#ifdef RTK_USE_CUDA
  #include "itkCudaImage.h"
  #include "RTKExport.h"
#endif

#include <itkImageSource.h>
#include <itkNumericTraits.h>
#include <itkVariableLengthVector.h>
#include <itkVectorImage.h>

namespace rtk
{
/** \class ConstantImageSource
 * \brief Generate an n-dimensional image with constant pixel values.
 *
 * ConstantImageSource generates an image with constant value. The filter is
 * useful to allow streaming of large images with a constant source, e.g., a
 * tomography reconstructed with a filtered backprojection algorithm.
 *
 * \test rtkRaycastInterpolatorForwardProjectionTest.cxx,
 * rtkProjectGeometricPhantomTest.cxx, rtkfdktest.cxx, rtkSARTTest.cxx,
 * rtkRampFilterTest.cxx, rtkAmsterdamShroudTest.cxx,
 * rtkDrawGeometricPhantomTest.cxx, rtkmotioncompensatedfdktest.cxx,
 * rtkFOVTest.cxx, rtkForwardProjectionTest.cxx, rtkdisplaceddetectortest.cxx,
 * rtkShortScanTest.cxx
 *
 * \author Simon Rit
 *
 * \ingroup RTK ImageSource
 */
template <typename TOutputImage>
class ITK_TEMPLATE_EXPORT ConstantImageSource : public itk::ImageSource<TOutputImage>
{
public:
#if ITK_VERSION_MAJOR == 5 && ITK_VERSION_MINOR == 1
  ITK_DISALLOW_COPY_AND_ASSIGN(ConstantImageSource);
#else
  ITK_DISALLOW_COPY_AND_MOVE(ConstantImageSource);
#endif

  /** Standard class type alias. */
  using Self = ConstantImageSource;
  using Superclass = itk::ImageSource<TOutputImage>;
  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;

  /** Typedef for the output image type. */
  using OutputImageType = TOutputImage;

  /** Typedefs for the output image PixelType. */
  using OutputImagePixelType = typename TOutputImage::PixelType;

  /** Typedef to describe the output image region type. */
  using OutputImageRegionType = typename TOutputImage::RegionType;

  /** Run-time type information (and related methods). */
  itkTypeMacro(ConstantImageSource, itk::ImageSource);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Basic types from the OutputImageType */
  using SizeType = typename TOutputImage::SizeType;
  using IndexType = typename TOutputImage::IndexType;
  using SpacingType = typename TOutputImage::SpacingType;
  using PointType = typename TOutputImage::PointType;
  using SizeValueType = typename SizeType::SizeValueType;
  typedef SizeValueType SizeValueArrayType[TOutputImage::ImageDimension];
  using SpacingValueType = typename TOutputImage::SpacingValueType;
  typedef SpacingValueType SpacingValueArrayType[TOutputImage::ImageDimension];
  using PointValueType = typename TOutputImage::PointValueType;
  typedef PointValueType PointValueArrayType[TOutputImage::ImageDimension];
  using DirectionType = typename TOutputImage::DirectionType;

  /** Set/Get size of the output image */
  itkSetMacro(Size, SizeType);
  itkGetMacro(Size, SizeType);
  virtual void
  SetSize(SizeValueArrayType sizeArray);
  virtual const SizeValueType *
  GetSize() const;

  /** Set/Get spacing of the output image */
  itkSetMacro(Spacing, SpacingType);
  itkGetMacro(Spacing, SpacingType);

  /** Set/Get origin of the output image */
  itkSetMacro(Origin, PointType);
  itkGetMacro(Origin, PointType);

  /** Set/Get direction of the output image */
  itkSetMacro(Direction, DirectionType);
  itkGetMacro(Direction, DirectionType);

  /** Set/Get index of the output image's largest possible region */
  itkSetMacro(Index, IndexType);
  itkGetMacro(Index, IndexType);

  /** Set/Get the pixel value of output */
  itkSetMacro(Constant, OutputImagePixelType);
  itkGetConstMacro(Constant, OutputImagePixelType);

  /** Set output image information from an existing image */
  void
  SetInformationFromImage(const itk::ImageBase<TOutputImage::ImageDimension> * image);

protected:
  ConstantImageSource();
  ~ConstantImageSource() override;
  void
  PrintSelf(std::ostream & os, itk::Indent indent) const override;

  void
  DynamicThreadedGenerateData(const OutputImageRegionType & outputRegionForThread) override;

  void
  GenerateOutputInformation() override;

  SizeType      m_Size;
  SpacingType   m_Spacing;
  PointType     m_Origin;
  DirectionType m_Direction;
  IndexType     m_Index;

  OutputImagePixelType m_Constant;
};

} // end namespace rtk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "rtkConstantImageSource.hxx"
#endif

#endif

/** Explicit instantiations */
#if defined(RTK_USE_CUDA) && !defined(ITK_TEMPLATE_EXPLICIT_ConstantImageSource)
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

extern template class RTK_EXPORT_EXPLICIT ConstantImageSource<itk::CudaImage<float, 3>>;
extern template class RTK_EXPORT_EXPLICIT ConstantImageSource<itk::CudaImage<float, 4>>;
extern template class RTK_EXPORT_EXPLICIT ConstantImageSource<itk::CudaImage<itk::CovariantVector<float, 3>, 3>>; // needed for itk::CudaImage<itk::CovariantVector<float, 3>, 3> in rtkADMMTotalVariationTest

ITK_GCC_PRAGMA_DIAG_POP()

} // end namespace rtk
#undef RTK_EXPORT_EXPLICIT
#endif
