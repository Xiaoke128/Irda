/* Nations Device PACK Add To IAR Tool
   使用说明和版本更新记录
 */
 
/* 1.使用说明 */
/*   i.  以管理员权限运行“Nations Device PACK Add To IAR Tool Vx.x.x.exe”
     ii. IAR安转目录选择，例如C:\Program Files (x86)\IAR Systems\Embedded Workbench 7.5
     iii.点击“安装”
*/

/* 2.用J-Link工具仿真时找不到芯片型号解决办法 */
/*  i.  找到J-Link安装目录，如C:\Program Files (x86)\SEGGER\JLink\
    ii  将J-Link安装目录中的JLinkARM.dll与JLinkConfig.exe这两个文件复制到IAR安装目录中的
        以下路径替换原有文件
            C:\Program Files (x86)\IAR Systems\Embedded Workbench 7.5\arm\bin\
        替换前建议先备份原有文件
    iii 将JLinkDevices.ref复制到IAR安装目录中的以下路径
            C:\Program Files (x86)\IAR Systems\Embedded Workbench 7.5\arm\bin\
        并修改JLinkDevices.ref文件内容为J-Link安装目录，如C:\Program Files (x86)\SEGGER\JLink\
*/

/* 3.版本更新记录 */
/*   
     V1.0.0 初始版本

     V1.1.0 安装时添加删除原有PACK包的弹窗选择

     V1.1.1 更新已知BUG

     V1.1.2 更新已知BUG
     
     V1.1.3 追加N32G435G8Q7型号
     
     V1.1.4 优化FLASH下载算法

     V1.1.5 追加N32G452CEL7型号、增加N32G435GBQ7
     
     V1.1.6 增加N32G452CCT7型号、修改设备寄存器描述错误

     V1.1.7 增加N32G455CEQ7型号
     V1.1.8 更新N32G4FR\G45x\WB452 svd文件
	 
     V1.1.9 增加N32G430系列相关型号，安装软件更新为英文版
*/
-------------------------------------------------------------------------------------
/* Nations Device PACK Add To IAR Tool
  Instructions for use and version update record
 */
 
/* 1. Instructions for use */
/*   i. Run "Nations Device PACK Add To IAR Tool Vx.x.x.exe" with administrator rights
      ii. IAR installation directory selection, such as C:\Program Files (x86)\IAR Systems\Embedded Workbench 7.5
      iii. Click "Install"
*/

/* 2. The solution to the chip model that cannot be found when simulating with the J-Link tool */
/* i. Find the J-Link installation directory, such as C:\Program Files (x86)\SEGGER\JLink\
   ii. Copy the JLinkARM.dll and JLinkConfig.exe files in the J-Link installation directory to the 
      following paths in the IAR installation directory and replace the original files:
	C:\Program Files (x86)\IAR Systems\Embedded Workbench 7.5\arm\bin\
      It is recommended to back up the original files before replacing
   iii. Copy the JLinkDevices.ref to the following path in the IAR installation directory:
	C:\Program Files (x86)\IAR Systems\Embedded Workbench 7.5\arm\bin\
       And modify the JLinkDevices.ref file content to the J-Link installation directory, such as C:\Program Files (x86)\SEGGER\JLink\
*/

/* 3.Version update record */
/*   
     V1.0.0 Initial version

     V1.1.0 Add the pop-up window option to delete the original PACK package when installing 

     V1.1.1 Update known BUG

     V1.1.2 Update known BUG
     
     V1.1.3 Added N32G435G8Q7 model
     
     V1.1.4 Optimized FLASH download algorithm

     V1.1.5 Adds N32G452CEL7、N32G435GBQ7
     
     V1.1.6 Adds N32G452CCT7, Modify device register description error

     V1.1.7 Adds N32G455CEQ7
     V1.1.8 Update N32G4FR\G45x\WB452 svd, Update the installation software to the English version
     
     V1.1.9 Added N32G430 series models, Updated them to English versions based on software
*/