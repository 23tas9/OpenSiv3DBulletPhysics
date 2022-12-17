# OpenSiv3DBulletPhysics
OpenSiv3Dで物理エンジンBulletを使うためのC++ライブラリ

## 対応形状
Box
Sphere
Cone
Cylinder

## サンプル
```cpp
#include <Siv3D.hpp> // OpenSiv3D v0.6.6
#include "SivBullet.hpp"

void Main() {
	// 3D シーンを描く、マルチサンプリング対応レンダーテクスチャ
	const MSRenderTexture rt{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };
	// 背景色 (removeSRGBCurve() で sRGB カーブを除去)
	Color bgColor = Palette::Skyblue.removeSRGBCurve();

	// デバッグカメラ
	DebugCamera3D camera{ rt.size(), 60_deg, Vec3{0, 30, -100}, Vec3{0, 0, 0} };

	// シミュレーション空間の定義 (重力 Vec3{ 0, -9.8, 0 })
	DynamicsWorld world{ Vec3{ 0, -9.8, 0 } };

	// 床
	// 質量 0.0 で { 0, 0, 0 } に { 100, 0.1, 100 } の大きさの箱
	auto ground = world.createBox(Vec3{ 0, 0, 0 }, Vec3{ 100, 0.1, 100 }, 0.0);

	// 箱の配列
	Array<BulletBody> boxes;

	// システムループ
	while (System::Update()) {
		// 空間の更新
		world.update(Scene::DeltaTime());

		// Enterキーで箱を追加
		if (KeyEnter.down()) {
			boxes << world.createBox(Vec3{ Random(-50, 50), 50, Random(-50, 50)}, Vec3{1, 1, 1}, 1.0);
		}

		// カメラの更新
		camera.update();

		// カメラを3D空間に設定
		Graphics3D::SetCameraTransform(camera);

		// [3D 描画]
		{
			const ScopedRenderTarget3D target{ rt.clear(bgColor) };

			// 床の描画
			ground.draw();
			// 箱の描画
			for (const auto& box : boxes) {
				box.draw();
			}
		}

		// [3D を 2D に描画]
		{
			Graphics3D::Flush();
			rt.resolve();
			Shader::LinearToScreen(rt);
		}
	}
}
```
