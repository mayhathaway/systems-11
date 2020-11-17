
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int random_nums() {

  int input_file = open("/dev/random", O_RDONLY);
  if (input_file == -1) {
    printf("error: %s\n", strerror(errno));
  }

  int num[1];

  int read_file = read(input_file, num, sizeof(num));
  if (read_file == -1) {
    printf("error: %s\n", strerror(errno));
  }
  close(input_file);
  return num[0];
}

int main () {
  int arr[10];
  printf("generating numbers to populate array...\n");
  int i;
  for (i = 0; i < 10; i++) {
    arr[i] = random_nums();
    printf("arr[%d]: %d\n", i, arr[i]);
  }

  int output_file = open("o.out", O_RDWR | O_CREAT, 0777);
  if (output_file == -1) {
    printf("error: %s\n", strerror(errno));
  }

  printf("writing to file...\n");
  int written_file = write(output_file, arr, sizeof(arr));
  if (written_file == -1) {
    printf("error: %s\n", strerror(errno));
  }

  printf("reading into a different array...\n");
  int diff_arr[10];
  written_file = read(output_file, diff_arr, sizeof(diff_arr));
  if (written_file == -1) {
    printf("error: %s\n", strerror(errno));
  }

  printf("printing content of different array...\n");
  for (i = 0; i < 10; i++) {
    printf("diff_arr[%d]: %d\n", i, diff_arr[i]);
  }

  close(output_file);

}
