
#include "rtkDrawSheppLoganFilter.h"
#include "itkCudaImage.h"

//#include "rtkCudaBackProjectionImageFilter.h"
//#include "rtkCudaRayCastBackProjectionImageFilter.h"

int
rtkTemplateTest2(int argc, char * argv[])
{
  if (argc < 2)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " reference.mha" << std::endl;
    return EXIT_FAILURE;
  }

  using OutputPixelType = float;
  constexpr unsigned int Dimension = 3;

  using OutputImageType = itk::CudaImage<OutputPixelType, Dimension>;

  // Generate a shepp logan phantom
  using DSLType = rtk::DrawSheppLoganFilter<OutputImageType, OutputImageType>;
  DSLType::Pointer dsl = DSLType::New();

  return EXIT_SUCCESS;
}
