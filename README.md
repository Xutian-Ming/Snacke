# Snacke
Greedy snake that eats snacks small kid game

观Tomthon learn something有感

同把大一的作业用cmake格式编译，并提交到github上

我也learn something

过程令人忍俊不禁

使用EasyX库 https://easyx.cn/easyx
lib文件夹下的静态库源自EasyX官网下载

Windows系统运行
1. https://jmeubank.github.io/tdm-gcc/download/ 下载并安装TDM-GCC（乃EasyX需求的版本），安装时勾选add to path
2. 下载Vscode
3. 下载CMake，Vscode中安装cmake插件，并指定Vscode的CMake配置
4. 创建build目录，在build目录下：
```powershell   
  cmake .. # 生成cmake build文件
  cmake --build . # 使用生成的cmake build文件 构建可执行文件exe exe位于bin文件夹内
```
5. 运行exe

Linux系统运行
1. 安装g++,gcc
2. 创建build目录，在build目录下：
```bash
  cmake .. 
  cmake --build .
``` 
3. 运行exe


