#include "config.h"

#include <stdlib.h>
#include <windows.h>

#include "os.h"
#include "options.h"
#include "lib.h"
#include "util.h"

/* -------------------------------------------------------------------------- */

const struct cmdline_options_s os_cmdline_options[] = {
    { NULL, 0, NULL, NULL, NULL, NULL }
};

/* -------------------------------------------------------------------------- */

static char *data_path = NULL;
static char *all_data_paths[] = { NULL, NULL, NULL };

/* -------------------------------------------------------------------------- */

static int os_make_path(const char *path)
{
    return -1;  /* FIXME */
}

/* -------------------------------------------------------------------------- */

const char *idstr_os = "win32";

int os_early_init(void)
{
    return 0;
}

int os_init(void)
{
    return 0;
}

void os_shutdown(void)
{
    lib_free(data_path);
    data_path = NULL;
}

const char **os_get_paths_data(void)
{
    int i = 0;
    if (data_path) {
        all_data_paths[i++] = data_path;
    }
    all_data_paths[i++] = ".";
    all_data_paths[i] = NULL;
    return (const char **)all_data_paths;
}

const char *os_get_path_data(void)
{
    return data_path;
}

void os_set_path_data(const char *path)
{
    data_path = lib_stralloc(path);
}

const char *os_get_path_user(void)
{
    return ".";
}

int os_make_path_user(void)
{
    return 0;
}

int os_make_path_for(const char *filename)
{
    int res = 0;
    char *path;
    util_fname_split(filename, &path, NULL);
    if ((path != NULL) && (path[0] != '.') && (path[1] != '\0')) {
        res = os_make_path(path);
        lib_free(path);
    }
    return res;
}

uint32_t os_get_time_us(void)
{
    return GetTickCount() * 1000;
}