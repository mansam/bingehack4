/* Copyright (c) Daniel Thaler, 2011 */
/* NetHack may be freely redistributed.  See license for details. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#include "nhcurses.h"

enum internal_commands {
    /* implicitly include enum nh_direction */
    UICMD_OPTIONS = DIR_SELF + 1,
    UICMD_EXTCMD,
    UICMD_REDO,
    UICMD_PREVMSG
};

struct nh_cmd_desc *keymap[KEY_MAX];
static struct nh_cmd_desc *commandlist;
static int cmdcount = 0;
static struct nh_cmd_desc *prev_cmd = NULL;
static struct nh_cmd_arg prev_arg = {CMD_ARG_NONE};
static int prev_count = 0;

static void init_keymap(void);

#define RESET_BINDINGS_ID (-10000)

#ifndef Ctrl
#define Ctrl(c)		(0x1f & (c))
#endif

#define DIRCMD		(1 << 29)
#define DIRCMD_SHIFT	(1 << 30)
#define DIRCMD_CTRL	(1 << 31)

struct nh_cmd_desc builtin_commands[] = {
    {"east",       "regular direction keys for movement,", 'l', 0, CMD_UI | DIRCMD | DIR_E},
    {"north",      "   spellcasting, etc.", 'k', 0, CMD_UI | DIRCMD | DIR_N},
    {"north_east", "", 'u', 0, CMD_UI | DIRCMD | DIR_NE},
    {"north_west", "", 'y', 0, CMD_UI | DIRCMD | DIR_NW},
    {"south",      "", 'j', 0, CMD_UI | DIRCMD | DIR_S},
    {"south_east", "", 'n', 0, CMD_UI | DIRCMD | DIR_SE},
    {"south_west", "", 'b', 0, CMD_UI | DIRCMD | DIR_SW},
    {"west",       "", 'h', 0, CMD_UI | DIRCMD | DIR_W},
    {"up",         "climb stairs or ladders", '<', 0, CMD_UI | DIRCMD | DIR_UP},
    {"down",       "go down stairs or ladders or jump into holes", '>', 0, CMD_UI | DIRCMD | DIR_DOWN},
    
    {"run_east",       "go in specified direction until you", 'L', 0, CMD_UI | DIRCMD_SHIFT | DIR_E},
    {"run_north",      "   hit a wall or run into something", 'K', 0, CMD_UI | DIRCMD_SHIFT | DIR_N},
    {"run_north_east", "", 'U', 0, CMD_UI | DIRCMD_SHIFT | DIR_NE},
    {"run_north_west", "", 'Y', 0, CMD_UI | DIRCMD_SHIFT | DIR_NW},
    {"run_south",      "", 'J', 0, CMD_UI | DIRCMD_SHIFT | DIR_S},
    {"run_south_east", "", 'N', 0, CMD_UI | DIRCMD_SHIFT | DIR_SE},
    {"run_south_west", "", 'B', 0, CMD_UI | DIRCMD_SHIFT | DIR_SW},
    {"run_west",       "", 'H', 0, CMD_UI | DIRCMD_SHIFT | DIR_W},
    
    {"go_east",       "run in direction <dir> until something", Ctrl('l'), 0, CMD_UI | DIRCMD_CTRL | DIR_E},
    {"go_north",      "   interesting is seen", Ctrl('k'), 0, CMD_UI | DIRCMD_CTRL | DIR_N},
    {"go_north_east", "", Ctrl('u'), 0, CMD_UI | DIRCMD_CTRL | DIR_NE},
    {"go_north_west", "", Ctrl('y'), 0, CMD_UI | DIRCMD_CTRL | DIR_NW},
    {"go_south",      "", Ctrl('j'), 0, CMD_UI | DIRCMD_CTRL | DIR_S},
    {"go_south_east", "", Ctrl('n'), 0, CMD_UI | DIRCMD_CTRL | DIR_SE},
    {"go_south_west", "", Ctrl('b'), 0, CMD_UI | DIRCMD_CTRL | DIR_SW},
    {"go_west",       "", Ctrl('h'), 0, CMD_UI | DIRCMD_CTRL | DIR_W},
    
    {"extcommand", "perform an extended command", '#', 0, CMD_UI | UICMD_EXTCMD},
    {"options",	   "show option settings, possibly change them", 'O', 0, CMD_UI | UICMD_OPTIONS},
    {"redo",	   "redo the previous command", '\001', 0, CMD_UI | UICMD_REDO},
    {"prevmsg",	   "list previously displayed messages", Ctrl('p'), 0, CMD_UI | UICMD_PREVMSG},
};


static struct nh_cmd_desc *doextcmd(void);


static struct nh_cmd_desc *find_command(const char *cmdname)
{
    int i, count;

    for (i = 0; i < cmdcount; i++)
	if (!strcmp(commandlist[i].name, cmdname))
	    return &commandlist[i];
    
    count = sizeof(builtin_commands)/sizeof(struct nh_cmd_desc);
    for (i = 0; i < count; i++)
	if (!strcmp(builtin_commands[i].name, cmdname))
	    return &builtin_commands[i];
    
    return NULL;
}


static void handle_internal_cmd(struct nh_cmd_desc **cmd,
			    struct nh_cmd_arg *arg, int *count)
{
    int id = (*cmd)->flags & ~(CMD_UI | DIRCMD | DIRCMD_SHIFT | DIRCMD_CTRL);
    switch (id) {
	case DIR_NW: case DIR_N: case DIR_NE:
	case DIR_E:              case DIR_W:
	case DIR_SW: case DIR_S: case DIR_SE:
	case DIR_UP: case DIR_DOWN:
	    arg->argtype = CMD_ARG_DIR;
	    arg->d = id;
	    if ((*cmd)->flags & DIRCMD)
		*cmd = find_command("move");
	    else if((*cmd)->flags & DIRCMD_SHIFT)
		*cmd = find_command("run");
	    else if((*cmd)->flags & DIRCMD_CTRL)
		*cmd = find_command("go2");
	    break;
	    
	case UICMD_OPTIONS:
	    display_options(FALSE);
	    *cmd = NULL;
	    break;
	
	case UICMD_EXTCMD:
	    *cmd = doextcmd();
	    break;
	    
	case UICMD_REDO:
	    *cmd = prev_cmd;
	    *arg = prev_arg;
	    *count = prev_count;
	    break;
	    
	case UICMD_PREVMSG:
	    doprev_message();
	    *cmd = NULL;
	    break;
    }
}


static int get_cmdkey(void)
{
    int key = ERR;
    int frame = 0;
    
    if (settings.blink)
	wtimeout(stdscr, 666); /* wait 2/3 of a second before switching */
    
    while (1) {
	if (player.x) { /* x == 0 is not a valid coordinate */
	    wmove(mapwin, player.y, player.x - 1);
	    wrefresh(mapwin);
	}
	
	curs_set(1);
	key = nh_wgetch(stdscr);
	/* reverse the translation performed by ncurses in number_pad mode */
	if (key == KEY_BACKSPACE) /* all other CTRL combinations apper to be OK */
	    key = Ctrl('h');
	curs_set(0);
	
	if (key != ERR)
	    break;
	
	draw_map(++frame);
    };
    draw_map(0);
    wtimeout(stdscr, -1);
    
    return key;
}


const char *get_command(int *count, struct nh_cmd_arg *arg)
{
    int key, key2, multi;
    char line[BUFSZ];
    struct nh_cmd_desc *cmd, *cmd2;
    
    do {
	multi = 0;
	cmd = NULL;
	arg->argtype = CMD_ARG_NONE;
	
	key = get_cmdkey();
	while ((key >= '0' && key <= '9') || (multi > 0 && key == KEY_BACKDEL)) {
	    if (key == KEY_BACKDEL)
		multi /= 10;
	    else {
		multi = 10 * multi + key - '0';
		if (multi > 0xffff)
		    multi /= 10;
	    }
	    sprintf(line, "Count: %d", multi);
	    key = curses_msgwin(line);
	};
	
	if (key == '\033' || key == '\n') /* filter out ESC and enter */
	    continue;
	
	*count = multi;
	cmd = keymap[key];
	
	if (cmd != NULL) {
	    /* handle internal commands. The command handler may alter
		* cmd, arg and count (redo does this) */
	    if (cmd->flags & CMD_UI) {
		handle_internal_cmd(&cmd, arg, count);
		if (!cmd) /* command was fully handled internally */
		    continue;
	    }
	    
	    /* if the command requres an arg AND the arg isn't set yet (by handle_internal_cmd) */
	    if (cmd->flags & CMD_ARG_DIR && arg->argtype != CMD_ARG_DIR) {
		key2 = nh_wgetch(stdscr);
		if (key2 == '\033') /* cancel silently */
		    continue;
		
		cmd2 = keymap[key2];
		if (cmd2 && (cmd2->flags & CMD_UI) && (cmd2->flags & DIRCMD)) {
		    arg->argtype = CMD_ARG_DIR;
		    arg->d = (enum nh_direction)(cmd2->flags & ~(CMD_UI | DIRCMD));
		} else
		    cmd = NULL;
	    }
	}
	
	if (!cmd) {
	    curses_msgwin("Bad command.");
	}
    } while (!cmd);
    
    newturn(); /* re-enable output if it was stopped */
    wmove(mapwin, player.y, player.x - 1);
    
    prev_cmd = cmd;
    prev_arg = *arg;
    prev_count = *count;
    
    return cmd->name;
}


enum nh_direction key_to_dir(int key)
{
    struct nh_cmd_desc *cmd = keymap[key];
    
    if (!cmd || !(cmd->flags & DIRCMD))
	return DIR_NONE;
    
    return (enum nh_direction) cmd->flags & ~(CMD_UI | DIRCMD);
}


/* here after #? - now list all full-word commands */
int doextlist(const char **namelist, const char **desclist, int listlen)
{
    char buf[BUFSZ];
    int i, icount = 0, size = listlen;
    struct nh_menuitem *items = malloc(sizeof(struct nh_menuitem) * size);

    for (i = 0; i < listlen; i++) {
	    sprintf(buf, " %s\t- %s.", namelist[i], desclist[i]);
	    add_menu_txt(items, size, icount, buf, MI_TEXT);
    }
    curses_display_menu(items, icount, "Extended Commands List", PICK_NONE, NULL);

    return 0;
}


/* here after # - now read a full-word command */
static struct nh_cmd_desc *doextcmd(void)
{
    int i, idx, size;
    struct nh_cmd_desc *retval = NULL;
    char cmdbuf[BUFSZ];
    const char **namelist, **desclist;
    static const char exthelp[] = "?";
    int *idxmap;
    
    size = 0;
    for (i = 0; i < cmdcount; i++)
	if (commandlist[i].flags & CMD_EXT)
	    size++;
    namelist = malloc((size+1) * sizeof(char*));
    desclist = malloc((size+1) * sizeof(char*));
    idxmap = malloc((size+1) * sizeof(int));
    
    /* add help */
    namelist[size] = exthelp;
    desclist[size] = "get this list of extended commands";
    idxmap[size] = 0;
       
    idx = 0;
    for (i = 0; i < cmdcount; i++) {
	if (commandlist[i].flags & CMD_EXT) {
	    namelist[idx] = commandlist[i].name;
	    desclist[idx] = commandlist[i].desc;
	    idx++;
	}
    }
    
    /* keep repeating until we don't run help */
    do {
	if (!curses_get_ext_cmd(cmdbuf, namelist, desclist, size+1))
	    break;
	
	if (!strcmp(cmdbuf, exthelp)) {
	    doextlist(namelist, desclist, size+1);
	    continue;
	}
	
	retval = find_command(cmdbuf);
	
	/* don't allow ui commands: they wouldn't be handled properly later on */
	if (!retval || (retval->flags & CMD_UI)) {
	    retval = NULL;
	    char msg[BUFSZ];
	    sprintf(msg, "%s: unknown extended command.", cmdbuf);
	    curses_msgwin(msg);
	}
    } while (!retval);

    free(namelist);
    free(desclist);
    free(idxmap);
    
    return retval;
}

/*----------------------------------------------------------------------------*/


/* read the user-configured keymap from keymap.conf.
 * Return TRUE if this succeeds, FALSE otherwise */
static boolean read_keymap(void)
{
    char filename[BUFSZ];
    char *data, *line, *endptr;
    int fd, size, pos, key, i;
    struct nh_cmd_desc *cmd;
    
    filename[0] = '\0';
    if (!get_gamedir(CONFIG_DIR, filename))
	return FALSE;
    strncat(filename, "keymap.conf", BUFSZ);
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
	return FALSE;
    
    size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    
    data = malloc(size + 1);
    read(fd, data, size);
    data[size] = '\0';
    close(fd);
    
    /* clear the EXT_CMD bit for all commands */
    for (i = 0; i < cmdcount; i++)
	commandlist[i].flags &= (~CMD_EXT);
    
    /* read the file */
    line = strtok(data, "\r\n");
    while (line) {
	/* find the first non-space after the first space (ie the second word) */
	pos = 0;
	while (!isspace(line[pos]))
	    pos++;
	while (isspace(line[pos]))
	    pos++;
	
	cmd = find_command(&line[pos]);
	if (!cmd && line[pos] != '-')
	    goto badmap;
	
	if (!strncmp(line, "EXT", 3)) {
	    if (cmd)
		cmd->flags |= CMD_EXT;
	} else {
	    key = strtol(line, &endptr, 16);
	    if (key == 0 || endptr == line)
		goto badmap;
	    
	    keymap[key] = cmd;
	}
	
	line = strtok(NULL, "\r\n");
    }
    
    
    free(data);
    return TRUE;
    
badmap:
    curses_msgwin("Bad/damaged keymap.conf. Reverting to defaults.");
    init_keymap();
    return FALSE;
}


/* store the keymap in keymap.conf */
static void write_keymap(void)
{
    int fd, i;
    unsigned int key;
    char filename[BUFSZ], buf[BUFSZ];
    
    filename[0] = '\0';
    if (!get_gamedir(CONFIG_DIR, filename))
	return;
    strncat(filename, "keymap.conf", BUFSZ);
    
    fd = open(filename, O_TRUNC | O_CREAT | O_RDWR, 0660);
    
    for (key = 1; key < KEY_MAX; key++) {
	sprintf(buf, "%x %s\n", key, keymap[key] ? keymap[key]->name : "-");
	write(fd, buf, strlen(buf));
    }
    
    for (i = 0; i < cmdcount; i++) {
	if (commandlist[i].flags & CMD_EXT) {
	    sprintf(buf, "EXT %s\n", commandlist[i].name);
	    write(fd, buf, strlen(buf));
	}
    }
    
    close(fd);
}


/* initialize the keymap with the default keys suggested by NetHack */
static void init_keymap(void)
{
    int i;
    int count = sizeof(builtin_commands)/sizeof(struct nh_cmd_desc);
    
    memset(keymap, 0, sizeof(keymap));
    
    /* num pad direction keys */
    keymap[KEY_UP] = find_command("north");
    keymap[KEY_DOWN] = find_command("south");
    keymap[KEY_LEFT] = find_command("west");
    keymap[KEY_RIGHT] = find_command("east");
    keymap[KEY_A1] = find_command("north_west");
    keymap[KEY_A3] = find_command("north_east");
    keymap[KEY_C1] = find_command("south_west");
    keymap[KEY_C3] = find_command("south_east");
    /* diagonal keypad keys are not necessarily reported as A1, A3, C1, C3 */
    keymap[KEY_HOME]  = find_command("north_west");
    keymap[KEY_PPAGE] = find_command("north_east");
    keymap[KEY_END]   = find_command("south_west");
    keymap[KEY_NPAGE] = find_command("south_east");
    
    /* every command automatically gets its default key */
    for (i = 0; i < cmdcount; i++)
	if (commandlist[i].defkey)
	    keymap[(unsigned int)commandlist[i].defkey] = &commandlist[i];
	
    for (i = 0; i < count; i++)
	if (builtin_commands[i].defkey)
	    keymap[(unsigned int)builtin_commands[i].defkey] = &builtin_commands[i];
    
    /* alt keys are assigned if the key is not in use */
    for (i = 0; i < cmdcount; i++) {
	if (commandlist[i].altkey && !keymap[(unsigned int)commandlist[i].altkey])
	    keymap[(unsigned int)commandlist[i].altkey] = &commandlist[i];
    }
    
    for (i = 0; i < count; i++) {
	if (builtin_commands[i].altkey &&
	    !keymap[(unsigned int)commandlist[i].altkey])
	    keymap[(unsigned int)builtin_commands[i].altkey] = &builtin_commands[i];
    }
    
}


void load_keymap(void)
{
    struct nh_cmd_desc *cmdlist = nh_get_commands(&cmdcount);
    
    commandlist = malloc(cmdcount * sizeof(struct nh_cmd_desc));
    memcpy(commandlist, cmdlist, cmdcount * sizeof(struct nh_cmd_desc));

    /* always init the keymap - read keymap might not set up every mapping */
    init_keymap();
    read_keymap();
}


void free_keymap(void)
{
    free(commandlist);
    commandlist = NULL;
}


/* add the description of a command to the keymap menu */
static void add_keylist_command(struct nh_cmd_desc *cmd,
				struct nh_menuitem *item, int id)
{
    char buf[BUFSZ];
    char keys[BUFSZ];
    const char *kname;
    int i, kl;
    
    keys[0] = '\0';
    for (i = 0; i < KEY_MAX; i++) {
	if (keymap[i] == cmd) {
	    kl = strlen(keys);
	    if (kl) {
		keys[kl++] = ' ';
		keys[kl] = '\0';
	    }
	    kname = keyname(i);
	    if (kname[0] == ' ')
		kname = "SPACE";
	    strcat(keys, kname);
	}
    }
    
    sprintf(buf, "%s%.15s\t%.50s\t%.16s", cmd->flags & CMD_EXT ? "#" : "",
	    cmd->name, cmd->desc, keys);
    set_menuitem(item, id, MI_NORMAL, buf, 0, FALSE);
}


/* display a menu to alter the key bindings for the given command */
static void command_settings_menu(struct nh_cmd_desc *cmd)
{
    char buf[BUFSZ];
    const char *kname;
    int i, n, size = 10, icount, selection[1];
    struct nh_menuitem *items = malloc(sizeof(struct nh_menuitem) * size);
    
    do {
	icount = 0;
	for (i = 0; i < KEY_MAX; i++) {
	    if (keymap[i] == cmd) {
		kname = keyname(i);
		if (kname[0] == ' ')
		    kname = "SPACE";
		sprintf(buf, "delete key %s", kname);
		add_menu_item(items, size, icount, i, buf, 0, FALSE);
	    }
	}
	
	add_menu_item(items, size, icount, -1, "Add a new key", 0, FALSE);
	if (!(cmd->flags & CMD_UI)) {
	    if (cmd->flags & CMD_EXT)
		add_menu_item(items, size, icount, -2,
			      "Don't use as an extended command", 0, FALSE);
	    else
		add_menu_item(items, size, icount, -2,
			      "Use as an extended command", 0, FALSE);
	}
	
	sprintf(buf, "Key bindings for %s", cmd->name);
	n = curses_display_menu(items, icount, buf, PICK_ONE, selection);
	if (n < 1)
	    break;
	
	/* int this menu, ids > 0 are used for "delete key" items and id is the
	 * actual key. Negative ids are used for the 2 static menu items */
	if (selection[0] > 0) /* delete a key */
	    keymap[selection[0]] = NULL;
	else if (selection[0] == -1) { /* add a key */
	    sprintf(buf, "Press the key you want to use for \"%s\"", cmd->name);
	    i = curses_msgwin(buf);
	    if (keymap[i]) {
		sprintf(buf, "That key is already in use by \"%s\"! Replace?", keymap[i]->name);
		if ('y' != curses_yn_function(buf, "yn", 'n'))
		    continue;
	    }
	    keymap[i] = cmd;
	    
	} else if (selection[0] == -2) { /* toggle extended command status */
	    cmd->flags = (cmd->flags ^ CMD_EXT);
	}
	    
    } while (n > 0);
    
    free(items);
}


static boolean set_command_keys(struct win_menu *mdat, int idx)
{
    int id = mdat->items[idx].id;
    struct nh_cmd_desc *cmd;
    
    if (id == RESET_BINDINGS_ID) {
	init_keymap(); /* fully reset the keymap */
	return TRUE;
    }
    
    if (id < 0)
	cmd = &builtin_commands[-(id+1)];
    else if (id > 0)
	cmd = &commandlist[id-1];
    
    command_settings_menu(cmd);
    
    return TRUE;
}


void show_keymap_menu(boolean readonly)
{
    int i, n, icount;
    struct nh_menuitem *items = malloc(sizeof(struct nh_menuitem) *
                                 (ARRAY_SIZE(builtin_commands) + cmdcount + 4));
    
    do {
	set_menuitem(&items[0], 0, MI_HEADING, "Command\tDescription\tKey", 0, FALSE);
	icount = 1;
	/* add builtin commands */
	for (i = 0; i < ARRAY_SIZE(builtin_commands); i++) {
	    add_keylist_command(&builtin_commands[i], &items[icount],
				readonly ? 0 : -(i+1));
	    icount++;
	}
	
	/* add NetHack commands */
	for (i = 0; i < cmdcount; i++) {
	    add_keylist_command(&commandlist[i], &items[icount],
				readonly ? 0 : (i+1));
	    icount++;
	}
	
	set_menuitem(&items[icount++], 0, MI_TEXT, "", 0, FALSE);
	set_menuitem(&items[icount++], RESET_BINDINGS_ID, MI_NORMAL,
		     "!!!\tReset all keybindings to built-in defaults\t!!!", 0, FALSE);

	n = curses_display_menu_core(items, icount, "Keymap", readonly ? PICK_NONE :
	                        PICK_ONE, NULL, 0, 0, COLS, LINES, set_command_keys);
    } while(n > 0);
    free(items);
    
    write_keymap();
}
