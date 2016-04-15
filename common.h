#define MAX_SIZE 1000000

enum Error
{
    INVALIDARGUMENTS,
    INVALIDFILE,
    INVALIDSIZE,
    READING,
    WRITING,
    PROCESSING,
    ALLOCATING
};

enum Boolean
{
    FALSE,
    TRUE
};

enum Boolean process_error(const enum Error error_code);

