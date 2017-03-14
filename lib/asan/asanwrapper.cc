#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <string>

void usage(const char* me) {
  static const char* usage_s = "Usage:\n"
    "  %s /system/bin/app_process <args>\n"
    "or, better:\n"
    "  setprop wrap.<nicename> %s\n";
  fprintf(stderr, usage_s, me, me);
  exit(1);
}

int main(int argc, char** argv) {
  if (argc < 2) {
    usage(argv[0]);
  }
  char** args = new char*[argc];
  // If we are wrapping app_process, replace it with app_process_asan.
  // TODO(eugenis): rewrite to <dirname>/asan/<basename>, if exists?
  if (strcmp(argv[1], "/system/bin/app_process") == 0) {
    args[0] = (char*)"/system/bin/asan/app_process";
  } else if (strcmp(argv[1], "/system/bin/app_process32") == 0) {
    args[0] = (char*)"/system/bin/asan/app_process32";
  } else if (strcmp(argv[1], "/system/bin/app_process64") == 0) {
    args[0] = (char*)"/system/bin/asan/app_process64";
  } else {
    args[0] = argv[1];
  }

  for (int i = 1; i < argc - 1; ++i)
    args[i] = argv[i + 1];
  args[argc - 1] = 0;

  for (int i = 0; i < argc - 1; ++i)
    printf("argv[%d] = %s\n", i, args[i]);

  execv(args[0], args);
}
