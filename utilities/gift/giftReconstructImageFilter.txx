/*=========================================================================

  Program:  GIFT Multi-level Multi-band Image Filter
  Module:   giftReconstructImageFilter.txx
  Language: C++
  Date:     2005/11/22
  Version:  0.2
  Author:   Dan Mueller [d.mueller@qut.edu.au]

  Copyright (c) 2005 Queensland University of Technology. All rights reserved.
  See giftCopyright.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __giftReconstructImageFilter_TXX
#define __giftReconstructImageFilter_TXX

//Includes
#include "giftReconstructImageFilter.h"

namespace gift
{

/////////////////////////////////////////////////////////
//Default Constructor
template <class TImage>
ReconstructImageFilter<TImage>::ReconstructImageFilter()
{
  //Initialise private variables
  this->m_NumberOfLevels     = 0;
  m_Writer = WriterType::New();
}


/////////////////////////////////////////////////////////
//PrintSelf()
template <class TImage>
void ReconstructImageFilter<TImage>
::PrintSelf(std::ostream& os, itk::Indent indent) const
{
    Superclass::PrintSelf(os, indent);
}


/////////////////////////////////////////////////////////
//ModifyInputOutputStorage()
template <class TImage>
void ReconstructImageFilter<TImage>
::ModifyInputOutputStorage()
{
    //Set as modified
    this->Modified();

    //Set required number of outputs
    unsigned int requiredNumberOfInputs = this->CalculateNumberOfInputs();
    this->SetNumberOfRequiredInputs(requiredNumberOfInputs);
}

template <class TImage>
unsigned int ReconstructImageFilter<TImage>::CalculateNumberOfInputs()
{
  unsigned int dimension = TImage::ImageDimension;
  unsigned int n = round(pow(2.0, dimension));
  return (m_NumberOfLevels * (n-1) +1);
}

template <class TImage>
void ReconstructImageFilter<TImage>
::GenerateAllKernelSources()
{
  unsigned int dimension = TImage::ImageDimension;
  unsigned int n = round(pow(2.0, dimension));

  // Create a vector of PassVector
  typename KernelSourceType::PassVector *passVectors = new typename KernelSourceType::PassVector[n];

  // Fill it with the right values
  unsigned int powerOfTwo = 1;
  for (unsigned int dim = 0; dim<dimension; dim++)
    {
    for (unsigned int vectIndex = 0; vectIndex < n; vectIndex++)
      {
      if ((int)floor(vectIndex / powerOfTwo)%2) passVectors[vectIndex][dim] = KernelSourceType::High;
      else passVectors[vectIndex][dim] = KernelSourceType::Low;
      }
    powerOfTwo *= 2;
    }

  // Generate all the kernel sources and store them into m_KernelSources
  for (unsigned int k=0; k<n; k++)
    {
    m_KernelSources.push_back(KernelSourceType::New());
    m_KernelSources[k]->SetPass(passVectors[k]);
    m_KernelSources[k]->SetReconstruction();
    m_KernelSources[k]->SetOrder(this->GetOrder());
    }
}

template <class TImage>
void ReconstructImageFilter<TImage>
::GenerateInputRequestedRegion()
{
  for (unsigned int i=0; i<this->CalculateNumberOfInputs(); i++)
    {
    InputImagePointer  inputPtr  = const_cast<TImage *>(this->GetInput(i));
    inputPtr->SetRequestedRegionToLargestPossibleRegion();
    }
}

template <class TImage>
void ReconstructImageFilter<TImage>
::GenerateOutputInformation()
{
//  for (unsigned int i=0; i<this->CalculateNumberOfInputs(); i++)
//    {
//    this->GetInput(i)->Print(std::cout);
//    }

  // n is the number of bands per level, including the ones
  // that will be Reconstructed and won't appear in the outputs
  unsigned int dimension = TImage::ImageDimension;
  unsigned int n = round(pow(2.0, dimension));

  // Before the cascade pipeline
  // Create and set the add filters
  for (unsigned int l=0; l<m_NumberOfLevels; l++)
    {
    m_AddFilters.push_back(AddFilterType::New());
    }

  // Create and set the kernel sources
  this->GenerateAllKernelSources();

  // Create all FFTConvolution and Downsampling filters
  for (unsigned int i=0; i<n * m_NumberOfLevels; i++)
    {
    m_ConvolutionFilters.push_back(ConvolutionFilterType::New());
    m_UpsampleFilters.push_back(UpsampleImageFilterType::New());
    }

  // Cascade pipeline
  // Set all the filters and connect them together
  unsigned int *upsamplingFactors = new unsigned int[dimension];
  for (unsigned int d=0; d<dimension; d++) upsamplingFactors[d]=2;

  for (unsigned int l=0; l<m_NumberOfLevels; l++)
    {
    for (unsigned int band=0; band<n; band++)
      {
      m_ConvolutionFilters[band + l*n]->SetInput(m_UpsampleFilters[band + l*n]->GetOutput());
      m_ConvolutionFilters[band + l*n]->SetKernelImage(m_KernelSources[band]->GetOutput());
      m_ConvolutionFilters[band + l*n]->SetOutputRegionModeToValid();

      m_AddFilters[l]->SetInput(band, m_ConvolutionFilters[band + l*n]->GetOutput());
      m_UpsampleFilters[band + l*n]->SetFactors(upsamplingFactors);
      m_UpsampleFilters[band + l*n]->SetOrder(this->m_Order);
      }
    if (l>0) m_UpsampleFilters[n*l]->SetInput(m_AddFilters[l-1]->GetOutput());
    }

  // Connect the upsample filters to the inputs of the pipeline
  unsigned int inputBand = 1;
  m_UpsampleFilters[0]->SetInput(this->GetInput(0));
  for (unsigned int i=0; i<n*m_NumberOfLevels; i++)
    {
    if (i%n)
      {
      m_UpsampleFilters[i]->SetInput(this->GetInput(inputBand));
      inputBand++;
      }
    }

  // Have the last filter calculate its output information
  // and copy it as the output information of the composite filter
  m_AddFilters[m_NumberOfLevels-1]->UpdateOutputInformation();
  this->GetOutput()->CopyInformation( m_AddFilters[m_NumberOfLevels-1]->GetOutput() );

  //Clean up
  delete[] upsamplingFactors;
}

template <class TImage>
void ReconstructImageFilter<TImage>
::GenerateData()
{
//  unsigned int dimension = TImage::ImageDimension;
//  unsigned int n = round(pow(2.0, dimension));

//  for (unsigned int l=0; l<m_NumberOfLevels; l++){
//      m_UpsampleFilters[n*l]->Update();
//      m_UpsampleFilters[n*l]->GetOutput()->Print(std::cout);
//    }

  // Have the last filter calculate its output image
  // and graft it to the output of the composite filter
  m_AddFilters[m_NumberOfLevels-1]->GraftOutput(this->GetOutput());
  m_AddFilters[m_NumberOfLevels-1]->Update();
  this->GraftOutput(m_AddFilters[m_NumberOfLevels-1]->GetOutput() );

//  for (unsigned int s=0; s<m_UpsampleFilters.size(); s++)
//    {
//    std::cout << "Printing output of upsample filter " << s << std::endl;
//    m_UpsampleFilters[s]->GetOutput()->Print(std::cout);
//    m_Writer->SetInput(m_UpsampleFilters[s]->GetOutput());
//    std::ostringstream os ;
//    os << s << ".mha";
//    m_Writer->SetFileName(os.str());
//    m_Writer->Update();
//    }
}


}// end namespace gift

#endif
