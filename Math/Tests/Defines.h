#ifndef TESTS_DEFINES_H_
#define TESTS_DEFINES_H_

//namespace 
//{
  /*
  typedef Math::Rotation3D<double> Rotation3D;
  typedef Math::Rotation3DZYX<double> Rotation3DZYX;
  typedef Math::Rotation3DX<double> Rotation3DX;
  typedef Math::Rotation3DY<double> Rotation3DY;
  typedef Math::Rotation3DZ<double> Potation3DZ;
  typedef Math::AxisAngle<double> AxisAngle;
  typedef Math::Translation3D<double> Translation3D;
  typedef Math::Transform3D<double> Transform3D;
  */

  using Math::PointXYZD;
  // reference points 
  const PointXYZD p000(0.,0.,0);
  const PointXYZD p100(1.,0.,0);
  const PointXYZD p010(0.,1.,0);
  const PointXYZD p001(0.,0.,1);
  const PointXYZD p110(1.,1.,0);
  const PointXYZD p101(1.,0.,1);
  const PointXYZD p011(0.,1.,1);
  const PointXYZD p111(1.,1.,1);

  const double cos45 = std::sqrt(2)/2.;
  const double PI = std::atan(1.0)*4;
//}

#endif
