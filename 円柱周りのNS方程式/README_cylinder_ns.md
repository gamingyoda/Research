# Cylinder Flow Solver

`cylinder_ns.c` は、円柱周りの 2 次元 Navier-Stokes 方程式を `r-θ` 系で扱う教育用コードです。壁面近傍の半径方向格子を幾何級数で密にし、渦度輸送式を陽的 Runge-Kutta 法で時間積分します。

## モデル

- 格子数: `100 x 100`
- 最小格子幅: `1.0e-5 m`
- 主流速度: `20.0 m/s`
- 円柱半径: `2.5e-4 m`
- 外側境界半径: `5.0e-3 m`
- 動粘性係数: `1.5e-5 m^2/s`
- 時間積分: 古典 4 次 Runge-Kutta

時間発展は完全に陽的です。流れ関数 `ψ` は各ステージで `∇²ψ = -ω` を反復で解いて更新しています。

## 実行方法

```sh
make
./cylinder_ns
gnuplot plot_cylinder.gnuplot
```

ステップ数と終了時刻は任意指定できます。

```sh
./cylinder_ns 1200 2.0e-4
```

## 出力ファイル

- `cylinder_field_final.dat`: 最終速度場・渦度場
- `cylinder_surface.dat`: 壁面せん断応力の近似値
- `cylinder_grid.dat`: 可視化用格子点
- `cylinder_history.dat`: 時刻歴
- `cylinder_speed.png`: 速度分布
- `cylinder_vorticity.png`: 渦度分布
- `cylinder_wall_shear.png`: 壁面せん断応力

## 補足

- 外側境界には円柱まわりのポテンシャル流を置いています。
- まず短時間計算で出力を確認し、必要なら `FINAL_TIME` や実行引数を伸ばして流れの発達を追ってください。
