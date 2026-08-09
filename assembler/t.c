#include <fsl.h>

string readFile(string filename, int *size)
{
	if(!filename)
		return NULL;

	fd_t file = open_file(filename, 0, 0);
	if(!file)
		return NULL;

	i32 sz = file_content_size(file);
	string buffer = allocate(0, sz + 1);

	int bytes = file_read(file, buffer, sz);
	if(bytes <= 0)
		fsl_warning("Unable to read file!");

	*size = sz;
	file_close(file);
	if(bytes > 0)
		return buffer;

	return NULL;
}

i8 get_next_token(string buffer, i64 *pos, int sz)
{
	for(; *pos < sz; (*pos)++)
	{
		if(buffer[*pos] == '\t' || buffer[*pos] == '\r' || buffer[*pos] == '\t')
			continue;

		return *pos;
	}

	return -1;
}

int entry()
{
	int sz = 0;
	string data = readFile("lul.n", &sz);
	i64 i = 0;
	while(get_next_token(data, &i, sz) != -1)
	{
		if(data[i] == '\n' || data[i] == ' ') {
			printc(data[i]);
			i++;
			continue;
		}

		printc(data[i]);
		i++;
	}
}
