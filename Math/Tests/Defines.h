#ifndef TESTS_DEFINES_H__
#define TESTS_DEFINES_H__

//namespace 
//{
  using Math::Rotation3D;
  using Math::Rotation3DZYX;
  using Math::Rotation3DX;
  using Math::Rotation3DY;
  using Math::Rotation3DZ;
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
