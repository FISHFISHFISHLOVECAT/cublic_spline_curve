import numpy as np
import matplotlib.pyplot as plt

# 读取数据
P = np.loadtxt('/home/junwu/Desktop/cpp/cubicspline/ctlPoint.txt')  # 100x3矩阵

# 创建3D图形
fig = plt.figure()
ax = fig.add_subplot(111)

# 绘制控制点
ax.scatter(P[:,0], P[:,1], color='r', marker='o', label='Control Points',s=100)


# 绘制连接控制点的线
ax.plot(P[:,0], P[:,1], color='r', linestyle='-', label='Spline Path')

# 设置坐标轴标签
ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
# ax.set_zlabel('Z Label')

# 读取插值点
Pinter = np.loadtxt('/home/junwu/Desktop/cpp/cubicspline/output.txt')  # 100x3矩阵

# 绘制插值点
ax.scatter(Pinter[:,0], Pinter[:,1], color='k', marker='o', label='Interpolated Points')

# 添加图例
ax.legend()

# 显示图形
plt.show()
