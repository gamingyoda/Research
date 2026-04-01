# 円柱周り2次元Navier-Stokes解析コード

`cylinder_ns_polar.c` は、円柱周りの2次元非圧縮Navier-Stokes方程式を `r-θ` 系で扱う課題向けコードです。
現行版は、前の単純な同心円表示より課題図に寄せるために、後流を強調した可視化へ調整しています。

- 格子点数: `110 x 140`
- 主流速度: `20 m/s`
- 最小格子幅: `1.0e-5 m`
- 時間積分: 陽的 `Runge-Kutta 4次`
- 壁面近傍: 半径方向に幾何級数格子を使って高密度化
- 描画: `dat` 出力 + `gnuplot`
- 出力画像: 上段に極座標格子、下段に下流の絶対速度分布

## 実行方法

```bash
make
./cylinder_ns_polar
```

または

```bash
make run
```

## 生成されるファイル

- `cylinder_ns_history.dat` : 収束履歴
- `cylinder_ns_field.dat` : 最終場の分布
- `cylinder_ns_grid.dat` : 格子形状
- `cylinder_ns_grid_wake.dat` : 後流強調表示用の格子
- `cylinder_ns_wake_map.dat` : 下流可視化用の直交座標マップ
- `cylinder_ns_polar.gp` : gnuplot スクリプト
- `cylinder_ns_overview.png` : 可視化画像

## 今回の仮定

PDF本文をこの環境でテキスト抽出できなかったため、円柱半径は

`R = 5.0e-3 m`

として実装しています。半径を変える場合は `cylinder_ns_polar.c` 冒頭の `CYLINDER_RADIUS` を修正してください。

## 注意

このコードは課題向けの簡略化モデルです。参照コードのような一般座標・圧縮性NS・乱流モデルまでは入れていません。
そのため、見た目は課題図に寄せていますが、物理的には「高Re数円柱後流の定性的な再現」に留まります。
