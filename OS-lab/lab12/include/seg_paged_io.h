#ifndef SEG_PAGED_IO_H
#define SEG_PAGED_IO_H

struct job_node;

void io_print_menu(void);
void io_print_unavailable(const char *feature_name);
void io_print_bitmap(void);
void io_print_job_detail(const struct job_node *job);
void io_print_message(const char *message);
void io_print_translation_result(const char *job_name, int segment_no, int page_no,
                                 int offset, int block_no, int physical_address);

#endif
