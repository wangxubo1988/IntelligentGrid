工程使用说明

	1.清除工程编译中间文件
		执行工程根目录下的project.cleanup脚本
	2.生成MAKEFILE文件
		在build目录下执行cmake ..
	3.编译工程
		在build目录下执行make，目标文件最后生成在工程根目录下的bin目录
	4.部署目标文件
		将bin下所有文件拷到目标板的usr/local/${项目名称}目录下，将所需动态库拷到目标板的lib目录下

	注：
		项目所有需要动态库
			0x00000001 (NEEDED)                     Shared library: [libxml2.so.2]
 			0x00000001 (NEEDED)                     Shared library: [libpthread.so.0]
 			0x00000001 (NEEDED)                     Shared library: [liblog4c.so.3]
 			0x00000001 (NEEDED)                     Shared library: [libsqlite3.so]
 			0x00000001 (NEEDED)                     Shared library: [libmpr.so]
 			0x00000001 (NEEDED)                     Shared library: [libm.so.6]
 			0x00000001 (NEEDED)                     Shared library: [libc.so.6]

		源代码编辑工具建议使用SourceInsight3.5（windows版本），避免出现乱码问题

		源码编译网络结构     
			centos编译服务器-》samba网络文件共享-》windows开发者电脑-》SourceInsight3.5编辑
		编译服务器与目标板网络
			centos编译服务器-》nfs网络文件共享-》目标板


		centos编译服务器IP：10.82.58.2
		目标板IP：10.82.58.80
