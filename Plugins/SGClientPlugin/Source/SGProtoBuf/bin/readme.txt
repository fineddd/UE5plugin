cmake -G "Visual Studio 17 2022" -DCMAKE_INSTALL_PREFIX=..\install -Dprotobuf_BUILD_TESTS=OFF ..

GOOGLE_PROTOBUF_INTERNAL_DONATE_STEAL_INLINE 报错
只需要根据错误定位到inlined_string_field.h文件的第430行，把#if改为#ifdef即可
port_def.inc 关闭部分警告 不然虚幻编译不过 #pragma warning(disable : 4800)


编译libprotobuf.lib 运行时库需要选择 md