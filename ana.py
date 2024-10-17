import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# 读取数据
P = np.loadtxt('/home/junwu/Desktop/cpp/cubicspline/ctlPoint.txt')  # 100x3矩阵

# 创建3D图形
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# 绘制控制点
ax.scatter(P[:,0], P[:,1], P[:,2], color='r', marker='o', label='Control Points',s=100)

# 在每个控制点上标注坐标
for i in range(len(P)):
    ax.text(P[i, 0], P[i, 1], P[i, 2], f'({P[i, 0]:.2f}, {P[i, 1]:.2f}, {P[i, 2]:.2f})', color='blue', fontsize=8)

# 绘制连接控制点的线
ax.plot(P[:,0], P[:,1], P[:,2], color='r', linestyle='-', label='Spline Path')

# 设置坐标轴标签
ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')

# 读取插值点
Pinter = np.loadtxt('/home/junwu/Desktop/cpp/cubicspline/output.txt')  # 100x3矩阵

# 绘制插值点
ax.scatter(Pinter[:,0], Pinter[:,1], Pinter[:,2], color='k', marker='o', label='Interpolated Points')

# 添加图例
ax.legend()

# 显示图形
plt.show()




