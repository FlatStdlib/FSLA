/*
    A loader, for x86_64 code to be pushed into this compiled binary 
    example: 
        gcc your_file.c -c
        cat your_file.o > loader (becomes the final binary for your_file)

    FOR DEBUGGING;
        0xD1D0 - gcc -nostdlib -c loader.c -ggdb; ld -o t loader.o /usr/lib/libfsl.a /usr/lib/loader.o
        0x62B0 - strip t

    PRODUCTION;
        0xCB20 - fsl loader.c -o t
        0x62B0 + 8 - strip t
*/
#include <fsl.h>

char FILENAME[10] = {0};
int entry(int argc, string argv[])
{
    trim_char_idx(argv[0], 0); 
    trim_char_idx(argv[0], 0);
    argv[0][1] = '\0';

    int len = str_len(argv[0]);
    mem_cpy(FILENAME, argv[0], len);

    uninit_mem();
    set_heap_sz(_HEAP_PAGE_ * 10);
    init_mem();

    fd_t fd = open_file(FILENAME, 0, 0);
    size_t sz = file_content_size(fd);

    if(__FSL_DEBUG__)
        println((const string)FILENAME), println(NULL);

    u8 *buff = allocate(0, sz + 1);
    int bytes = file_read(fd, buff, sz);

    if(__FSL_DEBUG__)
        printi(sz), println(NULL);

    buff += 0x62B0 + 8;
    char byte[4];
    if(buff[0] != 'L' || buff[1] != 'B' || buff[2] != 'E')
        return -1;
    
    for(int i = 0; i < sz - (0x62B0 + 8); i++)
    {
        byte_to_hex(buff[i], byte);
        print(byte), print(", ");
    }

    return 0;
}