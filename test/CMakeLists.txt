itk_module_test()

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/rtkTestConfiguration.h.in
  ${RTK_BINARY_DIR}/rtkTestConfiguration.h)

#-----------------------------------------------------------------------------
# RTK tests

set(RTKTests
  rtkBioscanTest.cxx
  rtkDisplacedDetectorTest.cxx
  rtkDisplacedDetectorCompOffsetTest.cxx
  rtkFbpParallelTest.cxx
  rtkFDKTest.cxx
  rtkImportTest.cxx
  rtkMotionCompensatedFDKTest.cxx
  rtkSARTTest.cxx
  rtkShortScanTest.cxx
  rtkRampFilterTest.cxx
  rtkRampFilterTest2.cxx
  rtkScatterGlareFilterTest.cxx
  rtkGainCorrectionTest.cxx
  rtkForwardProjectionTest.cxx
  rtkForwardAttenuatedProjectionTest.cxx
  rtkZengForwardProjectionTest.cxx
  rtkGeometryFileTest.cxx
  rtkReg23ProjectionGeometryTest.cxx
  rtkFOVTest.cxx
  rtkBinningTest.cxx
  rtkL0GradientNormTest.cxx
  rtkWaterPreCorrectionTest.cxx
  rtkLUTBasedVarI0RawToAttTest.cxx
  rtkDecomposeSpectralProjectionsTest.cxx
  rtkSpectralOneStepTest.cxx
  rtkVectorImageConvertersTest.cxx
  rtkAmsterdamShroudTest.cxx
  rtkVarianTest.cxx
  rtkElektaTest.cxx
  rtkLUTTest.cxx
  rtkImagXTest.cxx
  rtkEdfTest.cxx
  rtkDigisensTest.cxx
  rtkXRadTest.cxx
  rtkProjectGeometricPhantomTest.cxx
  rtkDrawGeometricPhantomTest.cxx
  rtkWeidingerForwardModelTest.cxx
  rtkNewtonUpdateTest.cxx
  rtkOSEMTest.cxx
  rtkFourDSARTTest.cxx
  rtkFourDConjugateGradientTest.cxx
  rtkWarpFourDToProjectionStackTest.cxx
  rtkWarpProjectionStackToFourDTest.cxx
  rtkCylindricalDetectorReconstructionTest.cxx
  rtkAdjointOperatorsTest.cxx
  rtkFourDAdjointOperatorsTest.cxx
  rtkInterpolateSplatAdjointTest.cxx
  rtkLaplacianTest.cxx
  rtkTotalVariationTest.cxx
  rtkGradientTest.cxx
  rtkDivergenceTest.cxx
  rtkLagCorrectionTest.cxx
  rtkConjugateGradientTest.cxx
  rtkWarpTest.cxx
  rtkI0EstimationTest.cxx
  rtkWaveletsTest.cxx
  rtkArgsInfoManagerTest.cxx
  rtkGeometryCloneTest.cxx
  rtkGeometryFromMatrixTest.cxx
  rtkOraTest.cxx
  rtkSelectOneProjPerCycleTest.cxx
  )

# We cannot compile these tests using CPU if GPU is present
# This is because of rtkIterativeConeBeamReconstructionFilter
if (NOT RTK_USE_CUDA)
  set(RTKTests
    ${RTKTests}
    rtkIterativeFDKTest.cxx
    rtkConjugateGradientReconstructionTest.cxx
    rtkFourDRoosterTest.cxx
    rtkADMMWaveletsTest.cxx
    rtkADMMTotalVariationTest.cxx
    rtkRegularizedConjugateGradientTest.cxx
    rtkCyclicDeformationTest.cxx
    )
endif()

CreateTestDriver(RTK "${RTK-Test_LIBRARIES}" "${RTKTests}")

itk_add_test(NAME rtkDisplacedDetectorTest COMMAND RTKTestDriver rtkDisplacedDetectorTest)
itk_add_test(NAME rtkDisplacedDetectorCompOffsetTest COMMAND RTKTestDriver rtkDisplacedDetectorCompOffsetTest)
itk_add_test(NAME rtkFBPParallelTest COMMAND RTKTestDriver rtkFbpParallelTest)
itk_add_test(NAME rtkFDKTest COMMAND RTKTestDriver rtkFDKTest)
itk_add_test(NAME rtkImportTest COMMAND RTKTestDriver rtkImportTest)
itk_add_test(NAME rtkMotionCompensatedFDKTest COMMAND RTKTestDriver rtkMotionCompensatedFDKTest)
itk_add_test(NAME rtkSARTTest COMMAND RTKTestDriver rtkSARTTest)
itk_add_test(NAME rtkBioscanTest COMMAND RTKTestDriver rtkBioscanTest
  DATA{Input/Bioscan/bioscan.dcm}
  DATA{Baseline/Bioscan/geometry.xml})
itk_add_test(NAME rtkShortScanTest COMMAND RTKTestDriver rtkShortScanTest)
itk_add_test(NAME rtkRampFilterTest COMMAND RTKTestDriver rtkRampFilterTest)
itk_add_test(NAME rtkRampFilterTest2 COMMAND RTKTestDriver rtkRampFilterTest2)
itk_add_test(NAME rtkScatterGlareFilterTest COMMAND RTKTestDriver rtkScatterGlareFilterTest)
itk_add_test(NAME rtkScatterGlareFilterNoFFTWTest COMMAND RTKTestDriver rtkScatterGlareFilterTest)
itk_add_test(NAME rtkGainCorrectionTest COMMAND RTKTestDriver rtkGainCorrectionTest)
itk_add_test(NAME rtkForwardProjectionTest COMMAND RTKTestDriver rtkForwardProjectionTest)
itk_add_test(NAME rtkForwardAttenuatedProjectionTest COMMAND RTKTestDriver rtkForwardAttenuatedProjectionTest)
itk_add_test(NAME rtkZengForwardProjectionTest COMMAND RTKTestDriver rtkZengForwardProjectionTest)
itk_add_test(NAME rtkGeometryFileTest COMMAND RTKTestDriver rtkGeometryFileTest)
itk_add_test(NAME rtkReg23ProjectionGeometryTest COMMAND RTKTestDriver rtkReg23ProjectionGeometryTest)
itk_add_test(NAME rtkFOVTest COMMAND RTKTestDriver rtkFOVTest)
itk_add_test(NAME rtkBinningTest COMMAND RTKTestDriver rtkBinningTest)
itk_add_test(NAME rtkL0GradientNormTest COMMAND RTKTestDriver rtkL0GradientNormTest)
itk_add_test(NAME rtkWaterPreCorrectionTest COMMAND RTKTestDriver rtkWaterPreCorrectionTest)
itk_add_test(NAME rtkLUTBasedVarI0RawToAttTest COMMAND RTKTestDriver rtkLUTBasedVarI0RawToAttTest)
itk_add_test(NAME rtkDecomposeSpectralProjectionsTest COMMAND RTKTestDriver rtkDecomposeSpectralProjectionsTest
  DATA{Input/Spectral/incident_spectrum.mha}
  DATA{Input/Spectral/detector_response.mha}
  DATA{Input/Spectral/material_attenuations.mha})
itk_add_test(NAME rtkSpectralOneStepTest COMMAND RTKTestDriver rtkSpectralOneStepTest
  DATA{Input/Spectral/OneStep/no_vector_incident_spectrum_64_rows.mha}
  DATA{Input/Spectral/OneStep/incident_spectrum_64_rows.mha}
  DATA{Input/Spectral/detector_response.mha}
  DATA{Input/Spectral/material_attenuations.mha})
itk_add_test(NAME rtkVectorImageConvertersTest COMMAND RTKTestDriver rtkVectorImageConvertersTest)
itk_add_test(NAME rtkAmsterdamShroudTest COMMAND RTKTestDriver rtkAmsterdamShroudTest
  DATA{Baseline/AmsterdamShroud/Amsterdam_crop.mha}
  DATA{Baseline/AmsterdamShroud/Amsterdam.mha})
itk_add_test(NAME rtkVarianTest COMMAND RTKTestDriver rtkVarianTest
  DATA{Input/Varian/raw.hnd}
  DATA{Input/Varian/acqui.xml}
  DATA{Input/Varian/Proj_00000.xim}
  DATA{Input/Varian/acqui_probeam.xml}
  DATA{Input/Varian/image_00052.hnc}
  DATA{Baseline/Varian/geometry.xml}
  DATA{Baseline/Varian/attenuation.mha}
  DATA{Baseline/Varian/geometryProBeam.xml}
  DATA{Baseline/Varian/attenuationProBeam.mha}
  DATA{Baseline/Varian/geometryHnc.xml}
  DATA{Baseline/Varian/attenuationHnc.mha})
itk_add_test(NAME rtkElektaTest COMMAND RTKTestDriver rtkElektaTest
  DATA{Input/Elekta/IMAGE.DBF}
  DATA{Input/Elekta/FRAME.DBF}
  DATA{Input/Elekta/raw.his}
  DATA{Input/Elekta/_Frames.xml}
  DATA{Baseline/Elekta/geometry.xml}
  DATA{Baseline/Elekta/attenuation.mha}
  DATA{Baseline/Elekta/geometry5.xml})
itk_add_test(NAME rtkLUTTest COMMAND RTKTestDriver rtkLUTTest
  DATA{Input/Elekta/raw.his}
  DATA{Baseline/Elekta/attenuation.mha})
itk_add_test(NAME rtkImagXTest COMMAND RTKTestDriver rtkImagXTest
  DATA{Input/ImagX/1.dcm}
  DATA{Input/ImagX/calibration.xml}
  DATA{Input/ImagX/room.xml}
  DATA{Input/ImagX/raw.xml,raw.raw}
  DATA{Baseline/ImagX/geo.xml}
  DATA{Baseline/ImagX/attenuation.mha}
  DATA{Baseline/ImagX/attenuationDCM.mha})
itk_add_test(NAME rtkEdfTest COMMAND RTKTestDriver rtkEdfTest
  DATA{Input/ESRF/raw.edf,dark.edf,refHST0000.edf}
  DATA{Baseline/ESRF/attenuation.mha})
itk_add_test(NAME rtkDigisensTest COMMAND RTKTestDriver rtkDigisensTest
  DATA{Input/Digisens/calibration.cal}
  DATA{Input/Digisens/ima0010.tif}
  DATA{Baseline/Digisens/geometry.xml}
  DATA{Baseline/Digisens/attenuation.mha})
itk_add_test(NAME rtkXRadTest COMMAND RTKTestDriver rtkXRadTest
  DATA{Input/XRad/SolidWater_HiGain1x1.header}
  DATA{Input/XRad/SolidWater_HiGain1x1_firstProj.header,flat.header,flat.img,dark.header,dark.img,SolidWater_HiGain1x1_firstProj.img}
  DATA{Baseline/XRad/geometry.xml}
  DATA{Baseline/XRad/attenuation.mha})
itk_add_test(NAME rtkProjectGeometricPhantomTest COMMAND RTKTestDriver rtkProjectGeometricPhantomTest
  DATA{Input/GeometricPhantom/SheppLogan.txt})
itk_add_test(NAME rtkDrawGeometricPhantomTest COMMAND RTKTestDriver rtkDrawGeometricPhantomTest
  DATA{Input/GeometricPhantom/SheppLogan.txt}
  DATA{Input/GeometricPhantom/Geometries.txt})
itk_add_test(NAME rtkWeidingerForwardModelTest COMMAND RTKTestDriver rtkWeidingerForwardModelTest
  DATA{Input/Spectral/OneStep/materialProjections.mha}
  DATA{Input/Spectral/OneStep/photonCounts.mha}
  DATA{Input/Spectral/OneStep/spectrum.mha}
  DATA{Input/Spectral/OneStep/projOfOnes.mha}
  DATA{Input/Spectral/OneStep/binnedDetectorResponse.csv}
  DATA{Input/Spectral/OneStep/materialAttenuations.csv}
  DATA{Baseline/Spectral/OneStep/out1.mha}
  DATA{Baseline/Spectral/OneStep/out2.mha})
itk_add_test(NAME rtkNewtonUpdateTest COMMAND RTKTestDriver rtkNewtonUpdateTest
  DATA{Input/Spectral/OneStep/gradient.mha}
  DATA{Input/Spectral/OneStep/hessian.mha}
  DATA{Baseline/Spectral/OneStep/newtonUpdate.mha})
itk_add_test(NAME rtkOSEMTest COMMAND RTKTestDriver rtkOSEMTest)
itk_add_test(NAME rtkFourDSARTTest COMMAND RTKTestDriver rtkFourDSARTTest)
itk_add_test(NAME rtkFourDConjugateGradientTest COMMAND RTKTestDriver rtkFourDConjugateGradientTest)
itk_add_test(NAME rtkWarpFourDToProjectionStackTest COMMAND RTKTestDriver rtkWarpFourDToProjectionStackTest)
itk_add_test(NAME rtkWarpProjectionStackToFourDTest COMMAND RTKTestDriver rtkWarpProjectionStackToFourDTest)
itk_add_test(NAME rtkCylindricalDetectorReconstructionTest COMMAND RTKTestDriver rtkCylindricalDetectorReconstructionTest)
itk_add_test(NAME rtkAdjointOperatorsTest COMMAND RTKTestDriver rtkAdjointOperatorsTest)
itk_add_test(NAME rtkFourDAdjointOperatorsTest COMMAND RTKTestDriver rtkFourDAdjointOperatorsTest
  DATA{Input/Phases/phases_slow.txt})
itk_add_test(NAME rtkInterpolateSplatAdjointTest COMMAND RTKTestDriver rtkInterpolateSplatAdjointTest
  DATA{Input/Phases/phases_slow.txt})
itk_add_test(NAME rtkLaplacianTest COMMAND RTKTestDriver rtkLaplacianTest
  DATA{Baseline/Laplacian/Laplacian.mha})
itk_add_test(NAME rtkTotalVariationTest COMMAND RTKTestDriver rtkTotalVariationTest)
itk_add_test(NAME rtkGradientTest COMMAND RTKTestDriver rtkGradientTest)
itk_add_test(NAME rtkDivergenceTest COMMAND RTKTestDriver rtkDivergenceTest)
itk_add_test(NAME rtkLagCorrectionTest COMMAND RTKTestDriver rtkLagCorrectionTest)
itk_add_test(NAME rtkConjugateGradientTest COMMAND RTKTestDriver rtkConjugateGradientTest)
itk_add_test(NAME rtkWarpTest COMMAND RTKTestDriver rtkWarpTest)
itk_add_test(NAME rtkI0EstimationTest COMMAND RTKTestDriver rtkI0EstimationTest)
itk_add_test(NAME rtkWaveletsTest COMMAND RTKTestDriver rtkWaveletsTest)
# Test the manager used to automatically clean up the gengetopt args_info structures
itk_add_test(NAME rtkArgsInfoManagerTest COMMAND RTKTestDriver rtkArgsInfoManagerTest)
itk_add_test(NAME rtkGeometryCloneTest COMMAND RTKTestDriver rtkGeometryCloneTest)
itk_add_test(NAME rtkGeometryFromMatrixTest COMMAND RTKTestDriver rtkGeometryFromMatrixTest)
itk_add_test(NAME rtkOraTest COMMAND RTKTestDriver rtkOraTest
  DATA{Input/Ora/0_afterLog.ora.xml,0_afterLog.mhd,0_afterLog.raw}
  DATA{Baseline/Ora/geometry.xml}
  DATA{Baseline/Ora/attenuation.mha})
itk_add_test(NAME rtkSelectOneProjPerCycleTest COMMAND RTKTestDriver rtkSelectOneProjPerCycleTest)


# We cannot compile these tests using CPU if GPU is present
# This is because of rtkIterativeConeBeamReconstructionFilter
if(NOT RTK_USE_CUDA)
  itk_add_test(NAME rtkIterativeFDKTest COMMAND RTKTestDriver rtkIterativeFDKTest)
  itk_add_test(NAME rtkConjugateGradientReconstructionTest COMMAND RTKTestDriver rtkConjugateGradientReconstructionTest)
  itk_add_test(NAME rtkFourDRoosterTest COMMAND RTKTestDriver rtkFourDRoosterTest)
  itk_add_test(NAME rtkADMMWaveletsTest COMMAND RTKTestDriver rtkADMMWaveletsTest)
  itk_add_test(NAME rtkADMMTotalVariationTest COMMAND RTKTestDriver rtkADMMTotalVariationTest
    DATA{Input/Phases/phases.txt}
    DATA{Input/Phases/phases_3projs.txt})
  itk_add_test(NAME rtkRegularizedConjugateGradientTest COMMAND RTKTestDriver rtkRegularizedConjugateGradientTest)
  itk_add_test(NAME rtkCyclicDeformationTest COMMAND RTKTestDriver rtkCyclicDeformationTest)
endif()

#-----------------------------------------------------------------------------
# RTK Cuda tests

if(RTK_USE_CUDA AND CUDA_HAVE_GPU)
  set(RTKCudaTests
    rtkCropTest.cxx
    rtkDisplacedDetectorTest.cxx
    rtkDisplacedDetectorCompCudaTest.cxx
    rtkDisplacedDetectorCompOffsetTest.cxx
    rtkFDKTest.cxx
    rtkFDKProjWeightCompCudaTest.cxx
    rtkImportTest.cxx
    rtkSARTTest.cxx
    rtkShortScanTest.cxx
    rtkShortScanCompCudaTest.cxx
    rtkRampFilterTest.cxx
    rtkRampFilterTest2.cxx
    rtkScatterGlareFilterTest.cxx
    rtkGainCorrectionTest.cxx
    rtkForwardProjectionTest.cxx
    rtkOSEMTest.cxx
    rtkFourDSARTTest.cxx
    rtkFourDConjugateGradientTest.cxx
    rtkWarpFourDToProjectionStackTest.cxx
    rtkWarpProjectionStackToFourDTest.cxx
    rtkCylindricalDetectorReconstructionTest.cxx
    rtkAdjointOperatorsTest.cxx
    rtkLaplacianTest.cxx
    rtkLagCorrectionTest.cxx
    rtkIterativeFDKTest.cxx
    rtkConjugateGradientReconstructionTest.cxx
    rtkFourDRoosterTest.cxx
    rtkADMMWaveletsTest.cxx
    rtkADMMTotalVariationTest.cxx
    rtkRegularizedConjugateGradientTest.cxx ##
    rtkCudaRaycastAdjointOperatorsTest.cxx
    rtkCyclicDeformationTest.cxx
    )

    ## rtkforbildtest

  CreateTestDriver(RTKCuda "${RTK-Test_LIBRARIES}" "${RTKCudaTests}")
  #set_target_properties(RTKCudaTestDriver PROPERTIES COMPILE_FLAGS -DUSE_CUDA)
  target_compile_definitions(RTKCudaTestDriver PRIVATE USE_CUDA)

  itk_add_test(NAME rtkCropFilterCudaTest COMMAND RTKCudaTestDriver rtkCropTest)
  itk_add_test(NAME rtkDisplacedDetectorCudaTest COMMAND RTKCudaTestDriver rtkDisplacedDetectorTest)
  itk_add_test(NAME rtkDisplacedDetectorCompCudaTest COMMAND RTKCudaTestDriver rtkDisplacedDetectorCompCudaTest)
  itk_add_test(NAME rtkDisplacedDetectorCompOffsetCudaTest COMMAND RTKCudaTestDriver rtkDisplacedDetectorCompOffsetTest)
  itk_add_test(NAME rtkFDKCudaTest COMMAND RTKCudaTestDriver rtkFDKTest)
  itk_add_test(NAME rtkFDKProjWeightCompCudaTest COMMAND RTKCudaTestDriver rtkFDKProjWeightCompCudaTest)
  itk_add_test(NAME rtkImportCudaTest COMMAND RTKCudaTestDriver rtkImportTest)
  itk_add_test(NAME rtkSARTCudaTest COMMAND RTKCudaTestDriver rtkSARTTest)
  itk_add_test(NAME rtkShortScanCudaTest COMMAND RTKCudaTestDriver rtkShortScanTest)
  itk_add_test(NAME rtkShortScanCompCudaTest COMMAND RTKCudaTestDriver rtkShortScanCompCudaTest)
  itk_add_test(NAME rtkRampFilterCudaTest COMMAND RTKCudaTestDriver rtkRampFilterTest)
  itk_add_test(NAME rtkRampFilterCudaTest2 COMMAND RTKCudaTestDriver rtkRampFilterTest2)
  itk_add_test(NAME rtkScatterGlareFilterCudaTest COMMAND RTKCudaTestDriver rtkScatterGlareFilterTest)
  itk_add_test(NAME rtkGainCorrectionCudaTest COMMAND RTKCudaTestDriver rtkGainCorrectionTest)
  itk_add_test(NAME rtkForwardProjectionCudaTest COMMAND RTKCudaTestDriver rtkForwardProjectionTest)
  itk_add_test(NAME rtkOSEMCudaTest COMMAND RTKCudaTestDriver rtkOSEMTest)
  itk_add_test(NAME rtkFourDSARTCudaTest COMMAND RTKCudaTestDriver rtkFourDSARTTest)
  itk_add_test(NAME rtkFourDConjugateGradientCudaTest COMMAND RTKCudaTestDriver rtkFourDConjugateGradientTest)
  itk_add_test(NAME rtkWarpFourDToProjectionStackCudaTest COMMAND RTKCudaTestDriver rtkWarpFourDToProjectionStackTest)
  itk_add_test(NAME rtkWarpProjectionStackToFourDCudaTest COMMAND RTKCudaTestDriver rtkWarpProjectionStackToFourDTest)
  itk_add_test(NAME rtkCylindricalDetectorReconstructionCudaTest COMMAND RTKCudaTestDriver rtkCylindricalDetectorReconstructionTest)
  itk_add_test(NAME rtkAdjointOperatorsCudaTest COMMAND RTKCudaTestDriver rtkAdjointOperatorsTest)
  itk_add_test(NAME rtkLaplacianCudaTest COMMAND RTKCudaTestDriver rtkLaplacianTest
    DATA{Baseline/Laplacian/Laplacian.mha})
  itk_add_test(NAME rtkLagCorrectionCudaTest COMMAND RTKCudaTestDriver rtkLagCorrectionTest)
  itk_add_test(NAME rtkIterativeFDKCudaTest COMMAND RTKCudaTestDriver rtkIterativeFDKTest)
  itk_add_test(NAME rtkConjugateGradientReconstructionCudaTest COMMAND RTKCudaTestDriver rtkConjugateGradientReconstructionTest)
  itk_add_test(NAME rtkFourDRoosterCudaTest COMMAND RTKCudaTestDriver rtkFourDRoosterTest)
  itk_add_test(NAME rtkADMMWaveletsCudaTest COMMAND RTKCudaTestDriver rtkADMMWaveletsTest)
  itk_add_test(NAME rtkADMMTotalVariationCudaTest COMMAND RTKCudaTestDriver rtkADMMTotalVariationTest
    DATA{Input/Phases/phases.txt}
    DATA{Input/Phases/phases_3projs.txt})
  itk_add_test(NAME rtkRegularizedConjugateGradientCudaTest COMMAND RTKCudaTestDriver rtkRegularizedConjugateGradientTest)
  itk_add_test(NAME rtkCudaRaycastAdjointOperatorsCudaTest COMMAND RTKCudaTestDriver rtkCudaRaycastAdjointOperatorsTest)
  itk_add_test(NAME rtkCyclicDeformationCudaTest COMMAND RTKCudaTestDriver rtkCyclicDeformationTest)

endif()

#-----------------------------------------------------------------------------
# Python tests

if(ITK_WRAP_PYTHON)
  itk_python_add_test(NAME rtkFirstReconstructionPythonTest COMMAND rtkFirstReconstruction.py ${CMAKE_CURRENT_BINARY_DIR}/rtkFirstReconstruction.mha)
endif()


# #-----------------------------------------------------------------------------
# # Find ITK.
# # Required to include ITK_USE_FILE in order to Register IO factories
# # Force requested modules to be RTK dependencies only, otherwise all
# # available factories will try to register themselves.
# if (NOT ITK_DIR)
  # set(ITK_DIR ${ITK_BINARY_DIR}/CMakeTmp)
# endif()
# find_package(ITK REQUIRED COMPONENTS ${ITK_MODULE_RTK_DEPENDS})
# include(${ITK_USE_FILE})

# # Use sha512 algorithm to generate content link
# if(NOT ITK_SOURCE_DIR)
  # set(ExternalData_LINK_CONTENT SHA512)
# endif()
