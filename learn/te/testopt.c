#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>

const char *vio_cfg_file;
time_t start_time;
time_t run_time = 0;
time_t end_time = 0;
int pipe_num;
int pipe_mask = 0;
int data_type;
int loop;
int need_cam;
int need_md;
int extra_action;
int need_free;
int need_get;
int need_m_thread;
int need_dump;
int need_order = 0;
int need_status;
int need_pym_feedback;
int need_gdc_process;
int need_gdc_fb = -1;
int need_pym_process;
int condition_time = 0;
int order_timeout = 34;
char *gdc_cfg = NULL;
char *gdc_cfg_opt = NULL;
char *raw_path[8];
char *g_cam_cfg_file = NULL;

const char *gdc_fb_pic = NULL;
int need_gdc_adv = 0;
char *raw_dir = NULL;
char *dis_data_dir = NULL;
int need_callback;
const char *pym_feedback_pic;
int need_bypass;
int bypass_opt[4];
pthread_t bypass_thid;
void vin_bypass_parse(char *optarg);


void vin_bypass_parse(char *optarg)
{
    char str[32];
    char *start = optarg, *tmp;
    int i = 0, v = 0;

    while (i < (sizeof(bypass_opt) / sizeof(bypass_opt[0])) && start && *start) {
        tmp = strchr(start, ',');
        if (tmp) {
            if (tmp != start && (tmp - start < sizeof(str))) {
                strncpy(str, start, (int)(tmp - start));
                str[tmp - start] = '\0';
                v = 1;
            }
            else {
                v = 0;
            }
            start = tmp + 1;
        }
        else {
            strncpy(str, start, sizeof(str));
            v = 1;
            start = NULL;
        }
        if (v) {
            bypass_opt[i] = atoi(str);
        }
        i++;
    }
    printf("bypass_port = %d\n", bypass_opt[0]);
    printf("bypass_enable = %d\n", bypass_opt[1]);
    if (bypass_opt[2] >= 0) {
        printf("bypass_mux = %d\n", bypass_opt[2]);
        if (bypass_opt[2] == 2) {
            printf("bypass_frame = %d\n", bypass_opt[3]);
        }
        else {
            printf("bypass_mask = %d\n", bypass_opt[3]);
        }
    }
}



/* void parse_raw_path_func(char *optarg)
{
    char *p = optarg, *d;
    int i = 0;
    printf("optarg %s\n", optarg);
    while (p && *p && i < PIPE_MAX) {
        d = strchr(p, ',');
        if (d)
            *d = '\0';
        raw_path[i] = p;
        printf("i %d raw_path[i] %s\n", i, raw_path[i]);
        i++;
        p = (d) ? (d + 1) : NULL;
    }
    return;
} */


void print_usage(const char *prog)
{
	printf("Usage: %s \n", prog);
	puts("  -v --vio_config       vio config file path\n"
		 "  -c --real_camera      real camera enable\n"
	     "  -r --run_time         time measured in seconds the program runs\n"
	     "  -p --pipe_id          pipe type\n"
	     "  -M --pipe_mask        pipe mask\n"
	     "  -t --data_type        data type\n"
	     "  -l --loop             need while/loop\n"
	     "  -f --free             need free data\n"
	     "  -g --get              need get data\n"
	     "  -m --multi_thread     multi thread get\n"
	     "  -d --dump             dump img\n"
	     "  -o --order            multi-cam order\n"
	     "  -O --timeout          multi-cam order timeout\n"
	     "  -S --stat             print status info\n"
	     "  -F --feedback         pym feedback\n"
	     "  -z --pym_fb_pic       pym feedbakc img\n"
	     "  -G --gdc_process	gdc process\n"
	     "  -P --process          need pym process\n"
	     "  -T --condition_time   get condition time\n"
		 "  -n --raw_feedback     get raw file path\n"
		 "  -N --dis_feedback     get dis file path\n"
		 "  -u --gdc_fb           gdc feedback process\n"
		 "  -U --gdc_bin_cfg_path gdc cfg bin path\n"
		 "  -V --gdc_opt_bin_cfg_path gdc opt cfg bin path\n"
		 "  -w --gdc_fb_pic       gdc fb pic\n"
		 "  -b --callback_enable  callback enable\n"
		 "  -B --bypass           port,enable,mux_sel,chn_mask\n"
		 "  -D --need_md          need_md\n"
		 "  -x --cam_cfg          camera cfg file\n"
		 "  -E --extra_action     extra_action\n"
		 "  -a --gdc_adv          gdc adv interface\n");
	exit(1);
}

void parse_opts(int argc, char *argv[])
{
	while (1) {
		static const char short_options[] =
		    "v:c:r:p:M:t:l:f:g:m:d:o:O:S:F:z:G:P:T:n:N:u:U:V:w:b:B:D:x:E:a:";
		static const struct option long_options[] = {
			{"vio_config", 1, 0, 'v'},
			{"real_camera", 1, 0, 'c'},
			{"run_time", 1, 0, 'r'},
			{"pipe_num", 1, 0, 'p'},
			{"pipe_mask", 1, 0, 'M'},
			{"data_type", 1, 0, 't'},
			{"loop", 1, 0, 'l'},
			{"free", 1, 0, 'f'},
			{"get", 1, 0, 'g'},
			{"multi_thread", 1, 0, 'm'},
			{"dump", 1, 0, 'd'},
			{"order", 1, 0, 'o'},
			{"timeout", 1, 0, 'O'},
			{"stat", 1, 0, 'S'},
			{"feedback", 1, 0, 'F'},
			{"pym_fb_pic", 1, 0, 'z'},
			{"gdc_process", 1, 0, 'G'},
			{"process", 1, 0, 'P'},
			{"condition_time", 1, 0, 'T'},
			{"raw_feedback", 1, 0, 'n'},
			{"dis_feedback", 1, 0, 'N'},
			{"gdc_fb", 1, 0, 'u'},
			{"gdc_bin_cfg", 1, 0, 'U'},
			{"gdc_bin_cfg_opt", 1, 0, 'V'},
			{"gdc_fb_pic", 1, 0, 'w'},
			{"callback_enable", 1, 0, 'b'},
			{"bypass", 1, 0, 'B'},
			{"need_md", 1, 0, 'D'},
			{"cam_cfg", 1, 0, 'x'},
			{"extra_action", 1, 0, 'E'},
			{"gdc_adv", 1, 0, 'a'},
			{NULL, 0, 0, 0},
		};

		int cmd_ret;

		cmd_ret =
		    getopt_long(argc, argv, short_options, long_options, NULL);

		if (cmd_ret == -1)
			break;

		switch (cmd_ret) {
		case 'v':
			vio_cfg_file = optarg;
			printf("vio_cfg_file = %s\n", vio_cfg_file);
			break;
		case 'c':
			need_cam = atoi(optarg);
			printf("need_cam = %d\n", need_cam);
			break;
		case 'r':
			run_time = atoi(optarg);
			printf("run_time = %ld\n", run_time);
			break;
		case 'p':
			pipe_num = atoi(optarg);
			printf("pipe_num = %d\n", pipe_num);
			break;
		case 'M':
			pipe_mask = atoi(optarg);
			printf("pipe_mask = %d\n", pipe_mask);
			break;
		case 't':
			data_type = atoi(optarg);
			printf("data_type = %d\n", data_type);
			break;
		case 'l':
			loop = atoi(optarg);
			printf("loop = %d\n", loop);
			break;
		case 'f':
			need_free = atoi(optarg);
			printf("need_free = %d\n", need_free);
			break;
		case 'g':
			need_get = atoi(optarg);
			printf("need_get = %d\n", need_get);
			break;
		case 'm':
			need_m_thread = atoi(optarg);
			printf("need_m_thread = %d\n", need_m_thread);
			break;
		case 'd':
			need_dump = atoi(optarg);
			printf("need_dump = %d\n", need_dump);
			break;
		case 'o':
			need_order = atoi(optarg);
			printf("need_order = %d\n", need_order);
			break;
		case 'O':
			order_timeout = atoi(optarg);
			printf("order_timeout = %d\n", order_timeout);
			break;
		case 'S':
			need_status = atoi(optarg);
			printf("need_status = %d\n", need_status);
			break;
		case 'F':
			need_pym_feedback = atoi(optarg);
			printf("need_pym_feedback = %d\n", need_pym_feedback);
			break;
		case 'z':
			pym_feedback_pic = optarg;
			printf("pym_feedback_pic = %s\n", pym_feedback_pic);
			break;
		case 'P':
			need_pym_process = atoi(optarg);
			printf("need_pym_process = %d\n", need_pym_process);
			break;
		case 'G':
			need_gdc_process = atoi(optarg);
			printf("need_gdc_process = %d\n", need_gdc_process);
			break;
		case 'T':
			condition_time = atoi(optarg);
			printf("condition_time = %d\n", condition_time);
			break;
		/* case 'n':
			parse_raw_path_func(optarg);
			break; */
		case 'N':
			dis_data_dir = optarg;
			printf("dis_data_dir = %s\n", dis_data_dir);
			break;
		case 'b':
			need_callback = atoi(optarg);
			printf("need_callback = %d\n", need_callback);
			break;
		case 'u':
			need_gdc_fb = atoi(optarg);
			printf("need_gdc_fb = %d\n", need_gdc_fb);
			break;
		case 'U':
			gdc_cfg = optarg;
			printf("gdc_cfg = %s\n", gdc_cfg);
			break;
		case 'V':
			gdc_cfg_opt = optarg;
			printf("gdc_cfg_opt = %s\n", gdc_cfg_opt);
			break;
		case 'w':
			gdc_fb_pic = optarg;
			printf("gdc_fb_pic = %s\n", gdc_fb_pic);
			break;
		case 'B':
			need_bypass = 1;
			printf("need_bypass = %d\n", need_bypass);
			vin_bypass_parse(optarg);
			break;
		case 'D':
			need_md = atoi(optarg);
			printf("need_md = %d\n", need_md);
			break;
		case 'x':
			g_cam_cfg_file = optarg;
			printf("cam_cfg_file = %s\n", g_cam_cfg_file);
			break;
		case 'E':
			extra_action = atoi(optarg);
			printf("extra_action = %d\n", extra_action);
			break;
		case 'a':
			need_gdc_adv = atoi(optarg);
			printf("extra_action = %d\n", need_gdc_adv);
			break;
		default:
			print_usage(argv[0]);
			break;
		}
	}
}



int main(int argc, char  *argv[])
{
    parse_opts(argc,argv);
	if (argc < 2)
    {
        print_usage(argv[0]);
        printf("leave, World! \n");
        exit(1);
    }
    return 0;
}


