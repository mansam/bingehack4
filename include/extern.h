/* Copyright (c) Steve Creps, 1988.				  */
/* NetHack may be freely redistributed.  See license for details. */

#ifndef EXTERN_H
#define EXTERN_H

#include "winprocs.h"

/* ### allmain.c ### */

extern void stop_occupation(void);

/* ### apply.c ### */

extern int doapply(void);
extern int dorub(void);
extern int dojump(void);
extern int jump(int);
extern int number_leashed(void);
extern void o_unleash(struct obj *);
extern void m_unleash(struct monst *, boolean);
extern void unleash_all(void);
extern boolean next_to_u(void);
extern struct obj *get_mleash(struct monst *);
extern void check_leash(xchar, xchar);
extern boolean um_dist(xchar, xchar, xchar);
extern boolean snuff_candle(struct obj *);
extern boolean snuff_lit(struct obj *);
extern boolean catch_lit(struct obj *);
extern void use_unicorn_horn(struct obj *);
extern boolean tinnable(struct obj *);
extern void reset_trapset(void);
extern void fig_transform(void *, long);
extern int unfixable_trouble_count(boolean);

/* ### artifact.c ### */

extern void init_artilist(void);
extern void init_artifacts(void);
extern void save_artifacts(int);
extern void restore_artifacts(struct memfile *mf);
extern const char *artiname(int);
extern struct obj *mk_artifact(struct obj *, aligntyp);
extern const char *artifact_name(const char *,short *);
extern boolean exist_artifact(int,const char *);
extern void artifact_exists(struct obj *,const char *, boolean);
extern int nartifact_exist(void);
extern boolean spec_ability(struct obj *,unsigned long);
extern boolean confers_luck(struct obj *);
extern boolean arti_reflects(struct obj *);
extern boolean restrict_name(struct obj *,const char *);
extern boolean defends(int,struct obj *);
extern boolean protects(int,struct obj *);
extern void set_artifact_intrinsic(struct obj *, boolean, long);
extern int touch_artifact(struct obj *,struct monst *);
extern int spec_abon(struct obj *,struct monst *);
extern int spec_dbon(struct obj *,struct monst *,int);
extern void discover_artifact(xchar);
extern boolean undiscovered_artifact(xchar);
extern int disp_artifact_discoveries(struct menulist *);
extern boolean artifact_hit(struct monst *,struct monst *,struct obj *,int *,int);
extern int doinvoke(void);
extern void arti_speak(struct obj *);
extern boolean artifact_light(struct obj *);
extern boolean artifact_has_invprop(struct obj *, uchar);
extern long arti_cost(struct obj *);

/* ### attrib.c ### */

extern boolean adjattrib(int,int,int);
extern void change_luck(schar);
extern int stone_luck(boolean);
extern void set_moreluck(void);
extern void gainstr(struct obj *,int);
extern void losestr(int);
extern void restore_attrib(void);
extern void exercise(int,boolean);
extern void exerchk(void);
extern void init_attr(int);
extern void redist_attr(void);
extern void adjabil(int,int);
extern int newhp(void);
extern schar acurr(int);
extern schar acurrstr(void);
extern void adjalign(int);

/* ### ball.c ### */

extern void ballfall(void);
extern void placebc(void);
extern void unplacebc(void);
extern void set_bc(int);
extern void move_bc(int,int,xchar,xchar,xchar,xchar);
extern boolean drag_ball(xchar,xchar,
		int *,xchar *,xchar *,xchar *,xchar *, boolean *,boolean);
extern void drop_ball(xchar,xchar,schar,schar);
extern void drag_down(void);

/* ### bones.c ### */

extern boolean can_make_bones(d_level *lev);
extern void savebones(struct obj *);
extern int getbones(d_level *levnum);

/* ### botl.c ### */

extern void bot(void);
extern int title_to_mon(const char *,int *,int *);
extern void max_rank_sz(void);
extern const char *rank_of(int, short, boolean);

/* ### cmd.c ### */

extern void reset_occupations(void);
extern void set_occupation(int (*)(void),const char *,int);
extern int get_command_idx(const char *cmd);
extern int do_command(int cmd, int, boolean, struct nh_cmd_arg*);
extern void enlightenment(int);
extern void show_conduct(int);
extern boolean dir_to_delta(enum nh_direction dir, schar *dx, schar *dy, schar *dz);
extern int xytod(schar, schar);
extern void dtoxy(coord *,int);
extern void confdir(schar *dx, schar *dy);
extern int get_adjacent_loc(const char *, const char *, xchar, xchar, coord *, schar *);
extern void sanity_check(void);

/* ### dbridge.c ### */

extern boolean is_pool(struct level *lev, int x, int y);
extern boolean is_lava(struct level *lev, int x, int y);
extern boolean is_ice(struct level *lev, int x, int y);
extern int is_drawbridge_wall(int,int);
extern boolean is_db_wall(int,int);
extern boolean find_drawbridge(int *,int*);
extern boolean create_drawbridge(struct level *lev, int x, int y, int dir, boolean flag);
extern void open_drawbridge(int,int);
extern void close_drawbridge(int,int);
extern void destroy_drawbridge(int,int);

/* ### decl.c ### */

void init_data(void);

/* ### detect.c ### */

extern int gold_detect(struct obj *);
extern int food_detect(struct obj *);
extern int object_detect(struct obj *,int);
extern int monster_detect(struct obj *,int);
extern int trap_detect(struct obj *);
extern void use_crystal_ball(struct obj *);
extern void do_mapping(void);
extern void do_vicinity_map(void);
extern void cvt_sdoor_to_door(struct rm *);
extern int findit(void);
extern int openit(void);
extern void find_trap(struct trap *);
extern int dosearch0(int);
extern int dosearch(void);
extern void sokoban_detect(struct level *lev);

/* ### dig.c ### */

extern boolean is_digging(void);
extern int holetime(void);
extern boolean dig_check(struct monst *, boolean, int, int);
extern void digactualhole(int,int,struct monst *,int);
extern int use_pick_axe(struct obj *);
extern int use_pick_axe2(struct obj *, schar, schar, schar);
extern boolean mdig_tunnel(struct monst *);
extern void watch_dig(struct monst *,xchar,xchar,boolean);
extern void zap_dig(schar, schar, schar);
extern void bury_objs(int,int);
extern void unearth_objs(struct level *lev, int x, int y);
extern void rot_organic(void *, long);
extern void rot_corpse(void *, long);

/* ### display.c ### */

#ifdef INVISIBLE_OBJECTS
extern struct obj * vobj_at(xchar,xchar);
#endif /* INVISIBLE_OBJECTS */
extern void clear_memory_glyph(schar x, schar y, int to);
extern void magic_map_background(xchar,xchar,int);
extern void map_background(xchar,xchar,int);
extern void map_trap(struct trap *,int);
extern void map_object(struct obj *,int);
extern void map_invisible(xchar,xchar);
extern void unmap_object(int,int);
extern void map_location(int,int,int);
extern void feel_location(xchar,xchar);
extern void newsym(int,int);
extern void shieldeff(xchar,xchar);
extern void tmp_at(int,int);
extern void under_ground(int);
extern void under_water(int);
extern void swallowed(int);
extern void see_monsters(void);
extern void set_mimic_blocking(void);
extern void see_objects(void);
extern void see_traps(void);
extern void display_self(void);
extern int doredraw(void);
extern int obfuscate_object(int otyp);
extern void dbuf_set(int x, int y, int bg, int trap, int obj, int obj_mn,
		   boolean invis, int mon, int monflags, int effect);
extern void dbuf_set_effect(int x, int y, int eglyph);
extern int dbuf_get_mon(int x, int y);
extern boolean warning_at(int x, int y);
extern void clear_display_buffer(void);
extern void cls(void);
extern void flush_screen_enable(void);
extern void flush_screen_disable(void);
extern void flush_screen(void);
extern int back_to_cmap(struct level *lev, xchar x, xchar y);
extern int zapdir_to_effect(int,int,int);
extern void dump_screen(FILE *dumpfp);
extern void set_wall_state(struct level *lev);

/* ### do.c ### */

extern int dodrop(void);
extern boolean boulder_hits_pool(struct obj *,int,int,boolean);
extern boolean flooreffects(struct obj *,int,int,const char *);
extern void doaltarobj(struct obj *);
extern boolean canletgo(struct obj *,const char *);
extern void dropx(struct obj *);
extern void dropy(struct obj *);
extern void obj_no_longer_held(struct obj *);
extern int doddrop(void);
extern int dodown(void);
extern int doup(void);
extern void notify_levelchange(void);
extern void goto_level(d_level *,boolean,boolean,boolean);
extern void schedule_goto(d_level *,boolean,boolean,int,
			     const char *,const char *);
extern void deferred_goto(void);
extern boolean revive_corpse(struct obj *);
extern void revive_mon(void *, long);
extern int donull(void);
extern int dowipe(void);
extern void set_wounded_legs(long,int);
extern void heal_legs(void);

/* ### do_name.c ### */

extern struct monst *christen_monst(struct monst *,const char *);
extern int do_mname(void);
extern struct obj *oname(struct obj *,const char *);
extern int do_naming(void);
extern void docall(struct obj *);
extern const char *rndghostname(void);
extern char *x_monnam(struct monst *,int,const char *,int,boolean);
extern char *l_monnam(struct monst *);
extern char *mon_nam(struct monst *);
extern char *noit_mon_nam(struct monst *);
extern char *Monnam(struct monst *);
extern char *noit_Monnam(struct monst *);
extern char *m_monnam(struct monst *);
extern char *y_monnam(struct monst *);
extern char *Adjmonnam(struct monst *,const char *);
extern char *Amonnam(struct monst *);
extern char *a_monnam(struct monst *);
extern char *distant_monnam(struct monst *,int,char *);
extern const char *rndmonnam(void);
extern const char *hcolor(const char *);
extern const char *rndcolor(void);
extern const char *roguename(void);
extern struct obj *realloc_obj(struct obj *, int, void *, int, const char *);
extern char *coyotename(struct monst *,char *);

/* ### do_wear.c ### */

extern void off_msg(struct obj *);
extern void set_wear(void);
extern boolean donning(struct obj *);
extern void cancel_don(void);
extern int Armor_off(void);
extern int Armor_gone(void);
extern int Helmet_off(void);
extern int Gloves_off(void);
extern int Boots_off(void);
extern int Cloak_off(void);
extern int Shield_off(void);
extern int Shirt_off(void);
extern void Amulet_off(void);
extern void Ring_on(struct obj *);
extern void Ring_off(struct obj *);
extern void Ring_gone(struct obj *);
extern void Blindf_on(struct obj *);
extern void Blindf_off(struct obj *);
extern int dotakeoff(void);
extern int doremring(void);
extern int cursed(struct obj *);
extern int canwearobj(struct obj *, long *, boolean);
extern int dowear(void);
extern int doputon(void);
extern void find_ac(void);
extern void glibr(void);
extern struct obj *some_armor(struct monst *);
extern void erode_armor(struct monst *,boolean);
extern struct obj *stuck_ring(struct obj *,int);
extern struct obj *unchanger(void);
extern void reset_remarm(void);
extern int doddoremarm(void);
extern int destroy_arm(struct obj *);
extern void adj_abon(struct obj *,schar);

/* ### dog.c ### */

extern void initedog(struct monst *);
extern struct monst *make_familiar(struct obj *,xchar,xchar,boolean);
extern struct monst *makedog(void);
extern void update_mlstmv(void);
extern void losedogs(void);
extern void mon_arrive(struct monst *,boolean);
extern void mon_catchup_elapsed_time(struct monst *,long);
extern void keepdogs(boolean);
extern void migrate_to_level(struct monst *,xchar,xchar,coord *);
extern int dogfood(struct monst *,struct obj *);
extern struct monst *tamedog(struct monst *,struct obj *);
extern void abuse_dog(struct monst *);
extern void wary_dog(struct monst *, boolean);

/* ### dogmove.c ### */

extern int dog_nutrition(struct monst *,struct obj *);
extern int dog_eat(struct monst *,struct obj *,int,int,boolean);
extern int dog_move(struct monst *,int);

/* ### dokick.c ### */

extern boolean ghitm(struct monst *,struct obj *);
extern void container_impact_dmg(struct obj *);
extern int dokick(void);
extern boolean ship_object(struct obj *,xchar,xchar,boolean);
extern void obj_delivery(void);
extern schar down_gate(xchar,xchar);
extern void impact_drop(struct obj *,xchar,xchar,xchar);

/* ### dothrow.c ### */

extern int dothrow(void);
extern int dofire(void);
extern void hitfloor(struct obj *);
extern void hurtle(int,int,int,boolean);
extern void mhurtle(struct monst *,int,int,int);
extern void throwit(struct obj *,long,boolean,schar,schar,schar);
extern int omon_adj(struct monst *,struct obj *,boolean);
extern int thitmonst(struct monst *,struct obj *);
extern int hero_breaks(struct obj *,xchar,xchar,boolean);
extern int breaks(struct obj *,xchar,xchar);
extern boolean breaktest(struct obj *);
extern boolean walk_path(coord *, coord *, boolean (*)(void *,int,int), void *);
extern boolean hurtle_step(void *, int, int);

/* ### dump.c ### */

extern void begin_dump(int how);
extern void end_dump(int how, char *kilbuf, char *pbuf, long umoney);
extern void dump_catch_menus(boolean intercept);

/* ### dungeon.c ### */

extern void save_dungeon(int,boolean,boolean);
extern void restore_dungeon(struct memfile *mf);
extern void insert_branch(branch *,boolean);
extern void init_dungeons(void);
extern s_level *find_level(const char *);
extern s_level *Is_special(d_level *);
extern branch *Is_branchlev(d_level *);
extern xchar ledger_no(d_level *);
extern xchar maxledgerno(void);
extern schar depth(d_level *);
extern xchar dunlev(d_level *);
extern xchar dunlevs_in_dungeon(d_level *);
extern xchar ledger_to_dnum(xchar);
extern xchar ledger_to_dlev(xchar);
extern xchar deepest_lev_reached(boolean);
extern boolean on_level(d_level *,d_level *);
extern void next_level(boolean);
extern void prev_level(boolean);
extern void u_on_newpos(int,int);
extern void u_on_sstairs(void);
extern void u_on_upstairs(void);
extern void u_on_dnstairs(void);
extern boolean On_stairs(xchar,xchar);
extern void get_level(d_level *,int);
extern boolean Is_botlevel(d_level *);
extern boolean can_fall_thru(struct level *lev);
extern boolean can_dig_down(struct level *lev);
extern boolean Can_rise_up(int,int,d_level *);
extern boolean In_quest(d_level *);
extern boolean In_mines(d_level *);
extern branch *dungeon_branch(const char *);
extern boolean at_dgn_entrance(const char *);
extern boolean In_hell(d_level *);
extern boolean In_V_tower(d_level *);
extern boolean On_W_tower_level(d_level *);
extern boolean In_W_tower(int,int,d_level *);
extern void find_hell(d_level *);
extern void goto_hell(boolean,boolean);
extern void assign_level(d_level *,d_level *);
extern void assign_rnd_level(d_level *,d_level *,int);
extern int induced_align(int);
extern boolean Invocation_lev(d_level *);
extern xchar level_difficulty(void);
extern schar lev_by_name(const char *);
extern schar print_dungeon(boolean,schar *,xchar *);

/* ### eat.c ### */

extern boolean is_edible(struct obj *);
extern void init_uhunger(void);
extern int Hear_again(void);
extern void reset_eat(void);
extern int doeat(void);
extern void gethungry(void);
extern void morehungry(int);
extern boolean is_fainted(void);
extern void reset_faint(void);
extern void violated_vegetarian(void);
extern void newuhs(boolean);
extern struct obj *floorfood(const char *,int);
extern void vomit(void);
extern int eaten_stat(int,struct obj *);
extern void food_disappears(struct obj *);
extern void food_substitution(struct obj *,struct obj *);
extern void fix_petrification(void);
extern void consume_oeaten(struct obj *,int);
extern boolean maybe_finished_meal(boolean);
extern void save_food(int fd);
extern void restore_food(struct memfile *mf);

/* ### end.c ### */

extern void terminate(void);
extern void panic(const char *,...);
extern int done2(void);
extern void done_in_by(struct monst *);
extern void done(int);
extern int num_genocides(void);
extern void display_rip(int how, char *kilbuf, char *pbuf, long umoney);

/* ### engrave.c ### */

extern char *random_engraving(char *);
extern void wipeout_text(char *,int,unsigned);
extern boolean can_reach_floor(void);
extern const char *surface(int,int);
extern const char *ceiling(int,int);
extern struct engr *engr_at(struct level *lev, xchar,xchar);
extern int sengr_at(const char *,xchar,xchar);
extern void u_wipe_engr(int);
extern void wipe_engr_at(struct level *lev, xchar x, xchar y, xchar cnt);
extern void read_engr_at(int,int);
extern void make_engr_at(struct level *lev, int,int,const char *,long,xchar);
extern void del_engr_at(struct level *lev, int,int);
extern int freehand(void);
extern int doengrave(void);
extern void save_engravings(int fd, struct level *lev, int mode);
extern void rest_engravings(struct memfile *mf, struct level *lev);
extern void del_engr(struct engr *);
extern void rloc_engr(struct engr *);
extern void make_grave(struct level *lev, int x, int y, const char *str);

/* ### exper.c ### */

extern int experience(struct monst *,int);
extern void more_experienced(int,int);
extern void losexp(const char *);
extern void newexplevel(void);
extern void pluslvl(boolean);
extern long rndexp(boolean);

/* ### explode.c ### */

extern void explode(int,int,int,int,char,int);
extern long scatter(int, int, int, unsigned int, struct obj *);
extern void splatter_burning_oil(int, int);

/* ### extralev.c ### */

extern void makeroguerooms(struct level *lev);
extern void makerogueghost(struct level *lev);

/* ### files.c ### */

extern void display_file(const char *, boolean);
extern FILE *fopen_datafile(const char *,const char *,int);
extern int create_bonesfile(char *bonesid, char errbuf[]);
extern void commit_bonesfile(char *bonesid);
extern int open_bonesfile(char *bonesid);
extern int delete_bonesfile(char *bonesid);
extern void paniclog(const char *, const char *);
extern boolean lock_fd(int fd, int retry);
extern void unlock_fd(int fd);

/* ### fountain.c ### */

extern void floating_above(const char *);
extern void dogushforth(int);
extern void dryup(xchar,xchar, boolean);
extern void drinkfountain(void);
extern void dipfountain(struct obj *);
extern void breaksink(int,int);
extern void drinksink(void);

/* ### hack.c ### */

extern boolean revive_nasty(int,int,const char*);
extern void movobj(struct obj *,xchar,xchar);
extern boolean may_dig(struct level *lev, xchar x, xchar y);
extern boolean may_passwall(struct level *lev, xchar x, xchar y);
extern boolean bad_rock(const struct permonst *,xchar,xchar);
extern boolean invocation_pos(xchar,xchar);
extern boolean test_move(int, int, int, int, int, int);
extern void domove(schar dx, schar dy, schar dz);
extern void invocation_message(void);
extern void spoteffects(boolean);
extern char *in_rooms(struct level *lev, xchar, xchar, int);
extern boolean in_town(int,int);
extern void check_special_room(boolean);
extern int dopickup(void);
extern void lookaround(void);
extern int monster_nearby(void);
extern void nomul(int nval, const char *msg);
extern void unmul(const char *);
extern void losehp(int,const char *,boolean);
extern int weight_cap(void);
extern int inv_weight(void);
extern int near_capacity(void);
extern int calc_capacity(int);
extern int max_capacity(void);
extern boolean check_capacity(const char *);
extern int inv_cnt(void);
#ifdef GOLDOBJ
extern long money_cnt(struct obj *);
#endif
extern int domovecmd(int,int,int);
extern int domovecmd_nopickup(int,int,int);
extern int dorun(int,int,int);
extern int dorun_nopickup(int,int,int);
extern int dogo(int,int,int);
extern int dogo2(int,int,int);
extern int dofight(int,int,int);

/* ### hacklib.c ### */

extern char *tabexpand(char *);
#ifndef STRNCMPI
extern int strncmpi(const char *,const char *,int);
#endif
extern void init_menulist(struct menulist *m);
extern boolean letter(char);
extern boolean digit(char);
extern char *eos(char *);
extern char lowc(char);
extern char highc(char);
extern char *lcase(char *);
extern char *upstart(char *);
extern char *mungspaces(char *);
extern char *s_suffix(const char *);
extern char *xcrypt(const char *,char *);
extern boolean onlyspace(const char *);
extern const char *ordin(int);
extern char *sitoa(int);
extern int sgn(int);
extern int rounddiv(long,int);
extern int dist2(int,int,int,int);
extern int distmin(int,int,int,int);
extern boolean online2(int,int,int,int);
extern boolean pmatch(const char *,const char *);
#ifndef STRSTRI
extern char *strstri(const char *,const char *);
#endif
extern boolean fuzzymatch(const char *,const char *,const char *,boolean);
extern int getyear(void);
extern long yyyymmdd(time_t);
extern int phase_of_the_moon(void);
extern boolean friday_13th(void);
extern int night(void);
extern int midnight(void);

/* ### invent.c ### */

extern void assigninvlet(struct obj *);
extern struct obj *merge_choice(struct obj *,struct obj *);
extern int merged(struct obj **,struct obj **);
extern void addinv_core1(struct obj *);
extern void addinv_core2(struct obj *);
extern struct obj *addinv(struct obj *);
extern struct obj *hold_another_object
		(struct obj *,const char *,const char *,const char *);
extern void useupall(struct obj *);
extern void useup(struct obj *);
extern void consume_obj_charge(struct obj *,boolean);
extern void freeinv_core(struct obj *);
extern void freeinv(struct obj *);
extern void delallobj(int,int);
extern void delobj(struct obj *);
extern struct obj *sobj_at(int otyp, struct level *lev, int x, int y);
extern struct obj *carrying(int);
extern boolean have_lizard(void);
extern struct obj *o_on(unsigned int,struct obj *);
extern boolean obj_here(struct obj *,int,int);
extern boolean wearing_armor(void);
extern boolean is_worn(struct obj *);
extern struct obj *gold_at(struct level *lev, int x, int y);
extern struct obj *mkgoldobj(long);
extern struct obj *getobj(const char *,const char *);
extern void fully_identify_obj(struct obj *);
extern void identify_pack(int);
extern void prinv(const char *,struct obj *,long);
extern char *xprname(struct obj *,const char *,char,boolean,long,long);
extern int ddoinv(void);
extern char display_inventory(const char *,boolean);
extern void update_inventory(void);
extern int display_binventory(int,int,boolean);
extern struct obj *display_cinventory(struct obj *);
extern struct obj *display_minventory(struct monst *,int,char *);
extern int dotypeinv(void);
extern boolean update_location(boolean all_objects);
extern int look_here(int,boolean);
extern int dolook(void);
extern boolean will_feel_cockatrice(struct obj *,boolean);
extern void feel_cockatrice(struct obj *,boolean);
extern void stackobj(struct obj *obj);
extern int doprgold(void);
extern int doprwep(void);
extern int doprarm(void);
extern int doprring(void);
extern int dopramulet(void);
extern int doprtool(void);
extern int doprinuse(void);
extern void useupf(struct obj *,long);
extern char *let_to_name(char,boolean);
extern void free_invbuf(void);
extern int doorganize(void);
extern int count_unpaid(struct obj *);
extern int count_buc(struct obj *,int);
extern void carry_obj_effects(struct obj *);
extern const char *currency(long);
extern void silly_thing(const char *,struct obj *);

/* ### light.c ### */

extern void new_light_source(struct level *lev, xchar x, xchar y,
			     int range, int type, void *id);
extern void del_light_source(struct level *lev, int type, void *id);
extern void do_light_sources(char **);
extern struct monst *find_mid(struct level *lev, unsigned nid, unsigned fmflags);
extern void transfer_lights(struct level *oldlev, struct level *newlev);
extern void save_light_sources(int fd, struct level *lev, int mode, int range);
extern void restore_light_sources(struct memfile *mf, struct level *lev);
extern void relink_light_sources(boolean ghostly, struct level *lev);
extern void obj_move_light_source(struct obj *, struct obj *);
extern boolean any_light_source(void);
extern void snuff_light_source(int, int);
extern boolean obj_sheds_light(struct obj *);
extern boolean obj_is_burning(struct obj *);
extern void obj_split_light_source(struct obj *, struct obj *);
extern void obj_merge_light_sources(struct obj *,struct obj *);
extern int candle_light_range(struct obj *);
extern int wiz_light_sources(void);

/* ### lock.c ### */

extern boolean picking_lock(int *,int *);
extern boolean picking_at(int,int);
extern void reset_pick(void);
extern int pick_lock(struct obj *);
extern int doforce(void);
extern boolean boxlock(struct obj *,struct obj *);
extern boolean doorlock(struct obj *,int,int);
extern int doopen(void);
extern int doclose(void);

/* ### log.c ### */

extern void log_newgame(int logfd, unsigned int rnd_seed, int playmode);
extern void log_command(int cmd, int count, struct nh_cmd_arg *arg);
extern void log_command_result(void);
extern void log_option(struct nh_option_desc *opt);
extern void log_getpos(int ret, int x, int y);
extern void log_getdir(enum nh_direction dir);
extern void log_query_key(char key, int *count);
extern void log_getlin(char *buf);
extern void log_yn_function(char key);
extern void log_menu(int n, int *results);
extern void log_objmenu(int n, struct nh_objresult *pick_list);
extern void log_bones(const char *bonesbuf, int buflen);
extern void log_finish(enum nh_log_status status);
extern void log_truncate(void);

/* ### logreplay.c ### */

extern void replay_set_logfile(int logfd);
extern void replay_begin(void);
extern void replay_end(void);
extern char *replay_bones(int *buflen);
extern void replay_setup_windowprocs(const struct nh_window_procs *procs);
extern void replay_read_newgame(time_t *seed, int *playmode, char *name);
extern void replay_run_cmdloop(boolean optonly);


/* ### makemon.c ### */

extern boolean is_home_elemental(const struct permonst *);
extern struct monst *clone_mon(struct monst *,xchar,xchar);
extern struct monst *makemon(const struct permonst *, struct level *lev,int,int,int);
extern boolean create_critters(int, const struct permonst *);
extern const struct permonst *rndmonst(void);
extern void reset_rndmonst(int);
extern const struct permonst *mkclass(char,int);
extern int adj_lev(const struct permonst *);
extern const struct permonst *grow_up(struct monst *,struct monst *);
extern int mongets(struct monst *,int);
extern int golemhp(int);
extern boolean peace_minded(const struct permonst *);
extern void set_malign(struct monst *);
extern void set_mimic_sym(struct monst *mtmp, struct level *lev);
extern int mbirth_limit(int);
extern void mimic_hit_msg(struct monst *,short);
#ifdef GOLDOBJ
extern void mkmonmoney(struct monst *, long);
#endif
extern void bagotricks(struct obj *);
extern boolean propagate(int,boolean,boolean);

/* ### mcastu.c ### */

extern int castmu(struct monst *, const struct attack *, boolean, boolean);
extern int buzzmu(struct monst *, const struct attack *);

/* ### mhitm.c ### */

extern int fightm(struct monst *);
extern int mattackm(struct monst *,struct monst *);
extern int noattacks(const struct permonst *);
extern int sleep_monst(struct monst *,int,int);
extern void slept_monst(struct monst *);
extern long attk_protection(int);

/* ### mhitu.c ### */

extern const char *mpoisons_subj(struct monst *, const struct attack *);
extern void u_slow_down(void);
extern struct monst *cloneu(void);
extern void expels(struct monst *,const struct permonst *,boolean);
extern const struct attack *getmattk(const struct permonst *,int,int *, struct attack *);
extern int mattacku(struct monst *);
extern int magic_negation(struct monst *);
extern int gazemu(struct monst *, const struct attack *);
extern void mdamageu(struct monst *,int);
extern int could_seduce(struct monst *,struct monst *, const struct attack *);
extern int doseduce(struct monst *);

/* ### minion.c ### */

extern void msummon(struct monst *);
extern void summon_minion(aligntyp,boolean);
extern int demon_talk(struct monst *);
extern long bribe(struct monst *);
extern int dprince(aligntyp);
extern int dlord(aligntyp);
extern int llord(void);
extern int ndemon(aligntyp);
extern int lminion(void);

/* ### mklev.c ### */

extern struct level *alloc_level(d_level *levnum);
extern void sort_rooms(struct level *lev);
extern void add_room(struct level *lev,int,int,int,int,boolean,schar,boolean);
extern void add_subroom(struct level *lev,struct mkroom *,int,int,int,int,
			   boolean,schar,boolean);
extern void makecorridors(struct level *lev);
extern void add_door(struct level *lev, int,int,struct mkroom *);
extern struct level *mklev(d_level *levnum);
extern void topologize(struct level *lev, struct mkroom *croom);
extern void place_branch(struct level *lev, branch *,xchar,xchar);
extern boolean occupied(struct level *lev, xchar x, xchar y);
extern int okdoor(struct level *lev, xchar, xchar);
extern void dodoor(struct level *lev, int,int,struct mkroom *);
extern void mktrap(struct level *lev, int,int,struct mkroom *,coord*);
extern void mkstairs(struct level *lev, xchar,xchar,char,struct mkroom *);
extern void mkinvokearea(void);

/* ### mkmap.c ### */

void flood_fill_rm(struct level *lev, int,int,int,boolean,boolean);
void remove_rooms(struct level *lev, int lx, int ly, int hx, int hy);

/* ### mkmaze.c ### */

extern void wallification(struct level *lev, int x1, int y1, int x2, int y2);
extern void walkfrom(struct level *lev, int,int);
extern void makemaz(struct level *lev, const char *);
extern void mazexy(struct level *lev, coord *cc);
extern void bound_digging(struct level *lev);
extern void mkportal(struct level *lev, xchar x, xchar y,
		     xchar todnum, xchar todlevel);
extern void place_lregion(struct level *lev, xchar,xchar,xchar,xchar,
			     xchar,xchar,xchar,xchar,
			     xchar,d_level *);
extern void movebubbles(void);
extern void water_friction(schar *, schar *);
extern void save_waterlevel(int,int);
extern void restore_waterlevel(struct memfile *mf);
extern const char *waterbody_name(xchar,xchar);

/* ### mkobj.c ### */

extern struct obj *mkobj_at(char let, struct level *lev, int x, int y, boolean artif);
extern struct obj *mksobj_at(int,struct level *,int,int,boolean,boolean);
extern struct obj *mkobj(struct level *lev, char oclass, boolean artif);
extern int rndmonnum(void);
extern struct obj *splitobj(struct obj *,long);
extern void replace_object(struct obj *,struct obj *);
extern void bill_dummy_object(struct obj *);
extern struct obj *mksobj(struct level *lev, int otyp, boolean init, boolean artif);
extern int bcsign(struct obj *);
extern int weight(struct obj *);
extern struct obj *mkgold(long amount, struct level *lev, int x, int y);
extern struct obj *mkcorpstat(int objtype, struct monst *mtmp,
			      const struct permonst *ptr, struct level *lev,
			      int x, int y, boolean init);
extern struct obj *obj_attach_mid(struct obj *, unsigned);
extern struct monst *get_mtraits(struct obj *, boolean);
extern struct obj *mk_tt_object(struct level *lev, int objtype, int x, int y);
extern struct obj *mk_named_object
	(int, const struct permonst *, int, int, const char *);
extern struct obj *rnd_treefruit_at(int x, int y);
extern void start_corpse_timeout(struct obj *);
extern void bless(struct obj *);
extern void unbless(struct obj *);
extern void curse(struct obj *);
extern void uncurse(struct obj *);
extern void blessorcurse(struct obj *,int);
extern boolean is_flammable(struct obj *);
extern boolean is_rottable(struct obj *);
extern void place_object(struct obj *otmp, struct level *lev, int x, int y);
extern void remove_object(struct obj *);
extern void discard_minvent(struct monst *);
extern void obj_extract_self(struct obj *);
extern void extract_nobj(struct obj *, struct obj **);
extern int add_to_minv(struct monst *, struct obj *);
extern struct obj *add_to_container(struct obj *, struct obj *);
extern void add_to_migration(struct obj *);
extern void add_to_buried(struct obj *obj);
extern void dealloc_obj(struct obj *);
extern void obj_ice_effects(int, int, boolean);
extern long peek_at_iced_corpse_age(struct obj *);
extern void obj_sanity_check(void);
extern void set_obj_level(struct level *lev, struct obj *obj);

/* ### mkroom.c ### */

extern void mkroom(struct level *lev, int roomtype);
extern void fill_zoo(struct level *lev, struct mkroom *sroom);
extern boolean nexttodoor(struct level *lev, int sx, int sy);
extern int somex(struct mkroom *);
extern int somey(struct mkroom *);
extern boolean inside_room(struct mkroom *,xchar,xchar);
extern boolean somexy(struct level *lev, struct mkroom *,coord *);
extern void mkundead(coord *,boolean,int);
extern const struct permonst *courtmon(void);
extern void save_rooms(int fd, struct level *lev);
extern void rest_rooms(struct memfile *mf, struct level *lev);
extern struct mkroom *search_special(struct level *lev, schar type);

/* ### mon.c ### */

extern int undead_to_corpse(int);
extern int genus(int,int);
extern int pm_to_cham(int);
extern int minliquid(struct monst *);
extern int movemon(void);
extern int meatmetal(struct monst *);
extern int meatobj(struct monst *);
extern void mpickgold(struct monst *);
extern boolean mpickstuff(struct monst *,const char *);
extern int curr_mon_load(struct monst *);
extern int max_mon_load(struct monst *);
extern boolean can_carry(struct monst *,struct obj *);
extern int mfndpos(struct monst *,coord *,long *,long);
extern boolean monnear(struct monst *,int,int);
extern void dmonsfree(struct level *lev);
extern int mcalcmove(struct monst*);
extern void mcalcdistress(void);
extern void replmon(struct monst *,struct monst *);
extern void relmon(struct monst *);
extern struct obj *mlifesaver(struct monst *);
extern boolean corpse_chance(struct monst *,struct monst *,boolean);
extern void mondead(struct monst *);
extern void mondied(struct monst *);
extern void mongone(struct monst *);
extern void monstone(struct monst *);
extern void monkilled(struct monst *,const char *,int);
extern void unstuck(struct monst *);
extern void killed(struct monst *);
extern void xkilled(struct monst *,int);
extern void mon_to_stone(struct monst*);
extern void mnexto(struct monst *);
extern boolean mnearto(struct monst *,xchar,xchar,boolean);
extern void poisontell(int);
extern void poisoned(const char *,int,const char *,int);
extern void m_respond(struct monst *);
extern void setmangry(struct monst *);
extern void wakeup(struct monst *);
extern void wake_nearby(void);
extern void wake_nearto(int,int,int);
extern void seemimic(struct monst *);
extern void resistcham(void);
extern void restartcham(void);
extern void restore_cham(struct monst *);
extern void mon_animal_list(boolean);
extern int newcham(struct monst *,const struct permonst *,boolean,boolean);
extern int can_be_hatched(int);
extern int egg_type_from_parent(int,boolean);
extern boolean dead_species(int,boolean);
extern void kill_genocided_monsters(void);
extern void golemeffects(struct monst *,int,int);
extern boolean angry_guards(boolean);
extern void pacify_guards(void);

/* ### mondata.c ### */

extern void set_mon_data(struct monst *,const struct permonst *,int);
extern const struct attack *attacktype_fordmg(const struct permonst *,int,int);
extern boolean attacktype(const struct permonst *,int);
extern boolean poly_when_stoned(const struct permonst *);
extern boolean resists_drli(struct monst *);
extern boolean resists_magm(struct monst *);
extern boolean resists_blnd(struct monst *);
extern boolean can_blnd(struct monst *,struct monst *,uchar,struct obj *);
extern boolean ranged_attk(const struct permonst *);
extern boolean hates_silver(const struct permonst *);
extern boolean passes_bars(const struct permonst *);
extern boolean can_track(const struct permonst *);
extern boolean breakarm(const struct permonst *);
extern boolean sliparm(const struct permonst *);
extern boolean sticks(const struct permonst *);
extern int num_horns(const struct permonst *);
extern boolean dmgtype(const struct permonst *,int);
extern int max_passive_dmg(struct monst *,struct monst *);
extern int monsndx(const struct permonst *);
extern int name_to_mon(const char *);
extern int gender(struct monst *);
extern int pronoun_gender(struct monst *);
extern boolean levl_follower(struct monst *);
extern int little_to_big(int);
extern int big_to_little(int);
extern const char *locomotion(const struct permonst *,const char *);
extern const char *stagger(const struct permonst *,const char *);
extern const char *on_fire(const struct permonst *, const struct attack *);
extern const struct permonst *raceptr(struct monst *);

/* ### monmove.c ### */

extern boolean itsstuck(struct monst *);
extern boolean mb_trapped(struct monst *);
extern void mon_regen(struct monst *,boolean);
extern int dochugw(struct monst *);
extern boolean onscary(int,int,struct monst *);
extern void monflee(struct monst *, int, boolean, boolean);
extern int dochug(struct monst *);
extern int m_move(struct monst *,int);
extern boolean closed_door(struct level *lev, int x, int y);
extern boolean accessible(int,int);
extern void set_apparxy(struct monst *);
extern boolean can_ooze(struct monst *);

/* ### mplayer.c ### */

extern struct monst *mk_mplayer(const struct permonst *ptr,
			 struct level *lev, xchar x, xchar y, boolean special);
extern void create_mplayers(int,boolean);
extern void mplayer_talk(struct monst *);

/* ### mthrowu.c ### */

extern int thitu(int,int,struct obj *,const char *);
extern int ohitmon(struct monst *,struct obj *,int,boolean);
extern void thrwmu(struct monst *);
extern int spitmu(struct monst *, const struct attack *);
extern int breamu(struct monst *, const struct attack *);
extern boolean linedup(xchar,xchar,xchar,xchar);
extern boolean lined_up(struct monst *);
extern struct obj *m_carrying(struct monst *,int);
extern void m_useup(struct monst *,struct obj *);
extern void m_throw(struct monst *,int,int,int,int,int,struct obj *);
extern boolean hits_bars(struct obj **,int,int,int,int);

/* ### mtrand.c ### */

extern void mt_srand(unsigned int seed);
extern unsigned int mt_random(void);
extern unsigned int mt_nextstate(void);
extern void save_mt_state(int fd);
extern void restore_mt_state(struct memfile *mf);
extern int display_rng(int);


/* ### muse.c ### */

extern boolean find_defensive(struct monst *);
extern int use_defensive(struct monst *);
extern int rnd_defensive_item(struct monst *);
extern boolean find_offensive(struct monst *);
extern int use_offensive(struct monst *);
extern int rnd_offensive_item(struct monst *);
extern boolean find_misc(struct monst *);
extern int use_misc(struct monst *);
extern int rnd_misc_item(struct monst *);
extern boolean searches_for_item(struct monst *,struct obj *);
extern boolean mon_reflects(struct monst *,const char *);
extern boolean ureflects(const char *,const char *);
extern boolean munstone(struct monst *,boolean);

/* ### music.c ### */

extern void awaken_soldiers(void);
extern int do_play_instrument(struct obj *);

/* ### o_init.c ### */

extern void init_objects(void);
extern int find_skates(void);
extern void oinit(void);
extern void savenames(int,int);
extern void restnames(struct memfile *mf);
extern void discover_object(int,boolean,boolean);
extern void undiscover_object(int);
extern int dodiscovered(void);

/* ### objnam.c ### */

extern char *obj_typename(int);
extern char *simple_typename(int);
extern boolean obj_is_pname(struct obj *);
extern char *distant_name(struct obj *,char *(*)(struct obj*));
extern char *fruitname(boolean);
extern char *xname(struct obj *);
extern char *mshot_xname(struct obj *);
extern boolean the_unique_obj(struct obj *obj);
extern char *doname(struct obj *);
extern boolean not_fully_identified(struct obj *);
extern char *corpse_xname(struct obj *,boolean);
extern char *cxname(struct obj *);
extern char *cxname2(struct obj *obj);
extern char *killer_xname(struct obj *);
extern const char *singular(struct obj *,char *(*)(struct obj*));
extern char *an(const char *);
extern char *An(const char *);
extern char *The(const char *);
extern char *the(const char *);
extern char *aobjnam(struct obj *,const char *);
extern char *Tobjnam(struct obj *,const char *);
extern char *otense(struct obj *,const char *);
extern char *vtense(const char *,const char *);
extern char *Doname2(struct obj *);
extern char *yname(struct obj *);
extern char *Yname2(struct obj *);
extern char *ysimple_name(struct obj *);
extern char *makeplural(const char *);
extern char *makesingular(const char *);
extern struct obj *readobjnam(char *,struct obj *,boolean);
extern int rnd_class(int,int);
extern const char *cloak_simple_name(struct obj *);
extern const char *mimic_obj_name(struct monst *);

/* ### options.c ### */

extern char *nh_getenv(const char *);
extern void init_opt_struct(void);
extern void cleanup_opt_struct(void);
extern void initoptions(void);
extern struct nh_option_desc *clone_optlist(const struct nh_option_desc *in);
extern void free_optlist(struct nh_option_desc *opt);
extern int dotogglepickup(void);
extern int fruitadd(char *);
#ifdef AUTOPICKUP_EXCEPTIONS
#error FIXME
extern int add_autopickup_exception(const char *);
extern void free_autopickup_exceptions(void);
#endif /* AUTOPICKUP_EXCEPTIONS */

/* ### pager.c ### */

extern int dowhatis(void);
extern int doquickwhatis(void);
extern int doidtrap(void);
extern int dowhatdoes(void);
extern int dohelp(void);
extern int dohistory(void);

/* ### pickup.c ### */

extern void add_valid_menu_class(int);
extern boolean allow_all(struct obj *);
extern boolean allow_category(struct obj *);
extern boolean is_worn_by_type(struct obj *);
extern int pickup(int);
extern int pickup_object(struct obj *, long, boolean);
extern int query_category(const char *, struct obj *, int,
				int*, int);
extern int obj_compare(const void *, const void *);
extern int query_objlist(const char *, struct obj *, int,
				struct object_pick **, int, boolean (*)(struct obj*));
extern void add_objitem(struct nh_objitem**, int*, enum nh_menuitem_role, int,
			int, char*, struct obj*, boolean);
extern struct obj *pick_obj(struct obj *);
extern int encumber_msg(void);
extern int doloot(void);
extern int use_container(struct obj *,int);
extern int loot_mon(struct monst *,int *,boolean *);
extern const char *safe_qbuf(const char *,unsigned,
				const char *,const char *,const char *);
extern boolean is_autopickup_exception(struct obj *, boolean);

/* ### pline.c ### */

extern void pline(const char *,...);
extern void impossible(const char *,...);
extern void Norep(const char *,...);
extern void free_youbuf(void);
extern void You_hear(const char *,...);
extern void verbalize(const char *,...);
extern void raw_printf(const char *,...);
extern const char *align_str(aligntyp);
extern void mstatusline(struct monst *);
extern void ustatusline(void);
extern void self_invis_message(void);

/* ### polyself.c ### */

extern void set_uasmon(void);
extern void change_sex(void);
extern void polyself(boolean);
extern int polymon(int);
extern void rehumanize(void);
extern int dobreathe(void);
extern int dospit(void);
extern int doremove(void);
extern int dospinweb(void);
extern int dosummon(void);
extern int dogaze(void);
extern int dohide(void);
extern int domindblast(void);
extern void skinback(boolean);
extern const char *mbodypart(struct monst *,int);
extern const char *body_part(int);
extern int poly_gender(void);
extern void ugolemeffects(int,int);

/* ### potion.c ### */

extern void set_itimeout(long *,long);
extern void incr_itimeout(long *,int);
extern void make_confused(long,boolean);
extern void make_stunned(long,boolean);
extern void make_blinded(long,boolean);
extern void make_sick(long, const char *, boolean,int);
extern void make_vomiting(long,boolean);
extern boolean make_hallucinated(long,boolean,long);
extern int dodrink(void);
extern int dopotion(struct obj *);
extern int peffects(struct obj *);
extern void healup(int,int,boolean,boolean);
extern void strange_feeling(struct obj *,const char *);
extern void potionhit(struct monst *,struct obj *,boolean);
extern void potionbreathe(struct obj *);
extern boolean get_wet(struct obj *);
extern int dodip(void);
extern void djinni_from_bottle(struct obj *);
extern struct monst *split_mon(struct monst *,struct monst *);
extern const char *bottlename(void);

/* ### pray.c ### */

extern int dosacrifice(void);
extern boolean can_pray(boolean);
extern int dopray(void);
extern const char *u_gname(void);
extern int doturn(void);
extern const char *a_gname(void);
extern const char *a_gname_at(xchar x,xchar y);
extern const char *align_gname(aligntyp);
extern const char *halu_gname(aligntyp);
extern const char *align_gtitle(aligntyp);
extern void altar_wrath(int,int);


/* ### priest.c ### */

extern int move_special(struct monst *,boolean,schar,boolean,boolean,
			   xchar,xchar,xchar,xchar);
extern char temple_occupied(char *);
extern int pri_move(struct monst *);
extern void priestini(struct level *lev, struct mkroom *,int,int,boolean);
extern char *priestname(struct monst *,char *);
extern boolean p_coaligned(struct monst *);
extern struct monst *findpriest(char);
extern void intemple(int);
extern void priest_talk(struct monst *);
extern struct monst *mk_roamer(const struct permonst *ptr, aligntyp alignment,
			struct level *lev, xchar x, xchar y, boolean peaceful);
extern void reset_hostility(struct monst *);
extern boolean in_your_sanctuary(struct monst *,xchar,xchar);
extern void ghod_hitsu(struct monst *);
extern void angry_priest(void);
extern void clearpriests(void);
extern void restpriest(struct monst *,boolean);

/* ### quest.c ### */

extern void onquest(void);
extern void nemdead(void);
extern void artitouch(void);
extern boolean ok_to_quest(void);
extern void quest_chat(struct monst *);
extern void quest_talk(struct monst *);
extern void quest_stat_check(struct monst *);
extern void finish_quest(struct obj *);

/* ### questpgr.c ### */

extern void load_qtlist(void);
extern void unload_qtlist(void);
extern short quest_info(int);
extern boolean is_quest_artifact(struct obj*);
extern void com_pager(int);
extern void qt_pager(int);
extern const struct permonst *qt_montype(void);

/* ### read.c ### */

extern int doread(void);
extern boolean is_chargeable(struct obj *);
extern void recharge(struct obj *,int);
extern void forget_objects(int);
extern void forget_levels(int);
extern void forget_traps(void);
extern void forget_map(int);
extern int seffects(struct obj *);
extern void litroom(boolean,struct obj *);
extern void do_genocide(int);
extern void punish(struct obj *);
extern void unpunish(void);
extern boolean cant_create(int *, boolean);
extern boolean create_particular(void);

/* ### rect.c ### */

extern void init_rect(void);
extern struct nhrect *get_rect(struct nhrect *);
extern struct nhrect *rnd_rect(void);
extern void split_rects(struct nhrect *,struct nhrect *);

/* ### region.c ### */
extern void run_regions(struct level *lev);
extern boolean in_out_region(struct level *lev, xchar x, xchar y);
extern boolean m_in_out_region(struct monst *,xchar,xchar);
extern void update_player_regions(struct level *lev);
extern void update_monster_region(struct monst *mon);
extern struct region *visible_region_at(struct level *lev, xchar x, xchar y);
extern void save_regions(int fd, struct level *lev, int mode);
extern void rest_regions(struct memfile *mf, struct level *lev, boolean ghostly);
extern struct region* create_gas_cloud(struct level *lev, xchar, xchar, int, long);

/* ### restore.c ### */

extern void inven_inuse(boolean);
extern int dorecover(int);
extern void trickery(char *);
extern struct level *getlev(struct memfile *mf, xchar levnum, boolean ghostly);
extern boolean lookup_id_mapping(unsigned, unsigned *);
extern void mread(struct memfile *mf,void *,unsigned int);

/* ### rnd.c ### */

extern int rn2(int);
extern int rnl(int);
extern int rnd(int);
extern int dice(int,int);
extern int rne(int);
extern int rnz(int);

/* ### role.c ### */

extern int randrole(void);
extern void role_init(void);
extern const char *Hello(struct monst *);
extern const char *Goodbye(void);
extern void rigid_role_checks(void);

/* ### rumors.c ### */

extern char *getrumor(int,char *, boolean);
extern void outrumor(int,int);
extern void save_oracles(int,int);
extern void restore_oracles(struct memfile *mf);
extern int doconsult(struct monst *);

/* ### save.c ### */

extern int dosave(void);
extern int dosave0(boolean emergency);
extern void savelev(int fd, xchar levnum, int mode);
extern void bwrite(int,void *,unsigned int);
extern void savefruitchn(int,int);
extern void free_dungeons(void);
extern void freedynamicdata(void);

/* ### shk.c ### */

#ifdef GOLDOBJ
extern long money2mon(struct monst *, long);
extern void money2u(struct monst *, long);
#endif
extern char *shkname(struct monst *);
extern void shkgone(struct monst *);
extern void set_residency(struct monst *,boolean);
extern void replshk(struct monst *,struct monst *);
extern void restshk(struct monst *,boolean);
extern char inside_shop(struct level *lev, xchar x, xchar y);
extern void u_left_shop(char *,boolean);
extern void remote_burglary(xchar,xchar);
extern void u_entered_shop(char *);
extern boolean same_price(struct obj *,struct obj *);
extern void shopper_financial_report(void);
extern int inhishop(struct monst *);
extern struct monst *shop_keeper(struct level *lev, char rmno);
extern boolean tended_shop(struct mkroom *);
extern void delete_contents(struct obj *);
extern void obfree(struct obj *,struct obj *);
extern void home_shk(struct monst *,boolean);
extern void make_happy_shk(struct monst *,boolean);
extern void hot_pursuit(struct monst *);
extern void make_angry_shk(struct monst *,xchar,xchar);
extern int dopay(void);
extern boolean paybill(int);
extern void finish_paybill(void);
extern struct obj *find_oid(unsigned id);
extern long contained_cost(struct obj *,struct monst *,long,boolean, boolean);
extern long contained_gold(struct obj *);
extern void picked_container(struct obj *);
extern long unpaid_cost(struct obj *);
extern void addtobill(struct obj *,boolean,boolean,boolean);
extern void splitbill(struct obj *,struct obj *);
extern void subfrombill(struct obj *,struct monst *);
extern long stolen_value(struct obj *,xchar,xchar,boolean,boolean);
extern void sellobj_state(int);
extern void sellobj(struct obj *,xchar,xchar);
extern int doinvbill(int);
extern struct monst *shkcatch(struct obj *,xchar,xchar);
extern void add_damage(xchar,xchar,long);
extern int repair_damage(struct monst *,struct damage *,boolean);
extern int shk_move(struct monst *);
extern void after_shk_move(struct monst *);
extern boolean is_fshk(struct monst *);
extern void shopdig(int);
extern void pay_for_damage(const char *,boolean);
extern boolean costly_spot(xchar,xchar);
extern struct obj *shop_object(xchar,xchar);
extern void price_quote(struct obj *);
extern void shk_chat(struct monst *);
extern void check_unpaid_usage(struct obj *,boolean);
extern void check_unpaid(struct obj *);
extern void costly_gold(xchar,xchar,long);
extern boolean block_door(xchar,xchar);
extern boolean block_entry(xchar,xchar);
extern char *shk_your(char *,struct obj *);
extern char *Shk_Your(char *,struct obj *);

/* ### shknam.c ### */

extern void stock_room(int shp_indx, struct level *lev, struct mkroom *sroom);
extern boolean saleable(struct monst *,struct obj *);
extern int get_shop_item(int);

/* ### sit.c ### */

extern void take_gold(void);
extern int dosit(void);
extern void rndcurse(void);
extern void attrcurse(void);

/* ### sounds.c ### */

extern void dosounds(void);
extern const char *growl_sound(struct monst *);
extern void growl(struct monst *);
extern void yelp(struct monst *);
extern void whimper(struct monst *);
extern void beg(struct monst *);
extern int dotalk(void);

/* ### sp_lev.c ### */

extern boolean check_room(struct level *lev, xchar *,xchar *,xchar *,xchar *,boolean);
extern boolean create_room(struct level *lev, xchar,xchar,xchar,xchar,
			xchar,xchar,xchar,xchar);
extern void create_secret_door(struct level *lev, struct mkroom *croom, xchar walls);
extern boolean dig_corridor(struct level *lev, coord *,coord *,boolean,schar,schar);
extern void fill_room(struct level *lev, struct mkroom *,boolean);
extern boolean load_special(struct level *lev, const char *);

/* ### spell.c ### */

extern int study_book(struct obj *);
extern void book_disappears(struct obj *);
extern void book_substitution(struct obj *,struct obj *);
extern void age_spells(void);
extern int docast(void);
extern int spell_skilltype(int);
extern int spelleffects(int,boolean);
extern void losespells(void);
extern int dovspell(void);
extern void dump_spells(void);
extern void initialspell(struct obj *);

/* ### steal.c ### */

#ifdef GOLDOBJ
extern long somegold(long);
#else
extern long somegold(void);
#endif
extern void stealgold(struct monst *);
extern void remove_worn_item(struct obj *,boolean);
extern int steal(struct monst *, char *);
extern int mpickobj(struct monst *,struct obj *);
extern void stealamulet(struct monst *);
extern void mdrop_special_objs(struct monst *);
extern void relobj(struct monst *,int,boolean);
#ifdef GOLDOBJ
extern struct obj *findgold(struct obj *);
#endif

/* ### steed.c ### */

extern void rider_cant_reach(void);
extern boolean can_saddle(struct monst *);
extern int use_saddle(struct obj *);
extern boolean can_ride(struct monst *);
extern int doride(void);
extern void exercise_steed(void);
extern void kick_steed(void);
extern void dismount_steed(int);
extern void place_monster(struct monst *mon, int x, int y);

/* ### symclass.c ### */

extern int def_char_to_objclass(char);
extern int def_char_to_monclass(char);

/* ### teleport.c ### */

extern boolean goodpos(struct level *lev, int,int,struct monst *,unsigned);
extern boolean enexto(coord *cc, struct level *lev, xchar xx, xchar yy,
	              const struct permonst *mdat);
extern boolean enexto_core(coord *cc, struct level *lev, xchar xx, xchar yy,
		           const struct permonst *mdat, unsigned entflags);
extern void teleds(int,int,boolean);
extern boolean safe_teleds(boolean);
extern boolean teleport_pet(struct monst *,boolean);
extern void tele(void);
extern int dotele(void);
extern void level_tele(void);
extern void domagicportal(struct trap *);
extern void tele_trap(struct trap *);
extern void level_tele_trap(struct trap *);
extern void rloc_to(struct monst *,int,int);
extern boolean rloc(struct monst *, boolean);
extern boolean tele_restrict(struct monst *);
extern void mtele_trap(struct monst *, struct trap *,int);
extern int mlevel_tele_trap(struct monst *, struct trap *,boolean,int);
extern void rloco(struct obj *);
extern int random_teleport_level(void);
extern boolean u_teleport_mon(struct monst *,boolean);

/* ### timeout.c ### */

extern void burn_away_slime(void);
extern void nh_timeout(void);
extern void fall_asleep(int, boolean);
extern void attach_egg_hatch_timeout(struct obj *);
extern void attach_fig_transform_timeout(struct obj *);
extern void kill_egg(struct obj *);
extern void learn_egg_type(int);
extern void begin_burn(struct obj *, boolean);
extern void end_burn(struct obj *, boolean);
extern void do_storms(void);
extern boolean start_timer(struct level *lev, long when, short kind,
			   short func_index, void *arg);
extern long stop_timer(struct level *lev, short func_index, void *arg);
extern void run_timers(void);
extern void obj_move_timers(struct obj *, struct obj *);
extern void obj_split_timers(struct obj *, struct obj *);
extern void obj_stop_timers(struct obj *);
extern boolean obj_is_local(struct obj *);
extern void transfer_timers(struct level *oldlev, struct level *newlev);
extern void save_timers(int fd, struct level *lev, int mode, int range);
extern void restore_timers(struct memfile *mf, struct level *lev, int range,
		           boolean ghostly, long adjust);
extern void relink_timers(boolean ghostly, struct level *lev);
extern int wiz_timeout_queue(void);
extern void timer_sanity_check(void);

/* ### topten.c ### */

extern void update_topten(int how);
extern struct obj *tt_oname(struct obj *);
extern void topten_level_name(int dnum, int dlev, char *outbuf);

/* ### track.c ### */

extern void initrack(void);
extern void settrack(void);
extern coord *gettrack(int,int);
extern void save_track(int fd);
extern void restore_track(struct memfile *mf);

/* ### trap.c ### */

extern boolean burnarmor(struct monst *);
extern boolean rust_dmg(struct obj *,const char *,int,boolean,struct monst *);
extern void grease_protect(struct obj *,const char *,struct monst *);
extern struct trap *maketrap(struct level *lev, int x, int y, int typ);
extern void fall_through(boolean);
extern struct monst *animate_statue(struct obj *,xchar,xchar,int,int *);
extern struct monst *activate_statue_trap(struct trap *,xchar,xchar,boolean);
extern void dotrap(struct trap *, unsigned);
extern void seetrap(struct trap *);
extern int mintrap(struct monst *);
extern void instapetrify(const char *);
extern void minstapetrify(struct monst *,boolean);
extern void selftouch(const char *);
extern void mselftouch(struct monst *,const char *,boolean);
extern void float_up(void);
extern void fill_pit(struct level *lev, int x, int y);
extern int float_down(long, long);
extern int fire_damage(struct obj *,boolean,boolean,xchar,xchar);
extern boolean water_damage(struct obj *,boolean,boolean);
extern boolean drown(void);
extern void drain_en(int);
extern int dountrap(void);
extern int untrap(boolean);
extern boolean chest_trap(struct obj *,int,boolean);
extern void deltrap(struct trap *);
extern boolean delfloortrap(struct trap *);
extern struct trap *t_at(struct level *lev, int x, int y);
extern void b_trapped(const char *,int);
extern boolean unconscious(void);
extern boolean lava_effects(void);
extern void blow_up_landmine(struct trap *);

/* ### u_init.c ### */

extern void u_init(void);

/* ### uhitm.c ### */

extern void hurtmarmor(struct monst *,int);
extern boolean attack_checks(struct monst *, struct obj *, schar, schar);
extern void check_caitiff(struct monst *);
extern schar find_roll_to_hit(struct monst *);
extern boolean attack(struct monst *, schar, schar);
extern boolean hmon(struct monst *,struct obj *,int);
extern int damageum(struct monst *, const struct attack *);
extern void missum(struct monst *, const struct attack *);
extern int passive(struct monst *,boolean,int,uchar);
extern void passive_obj(struct monst *,struct obj *, const struct attack *);
extern void stumble_onto_mimic(struct monst *, schar, schar);
extern int flash_hits_mon(struct monst *,struct obj *);

/* ### vault.c ### */

extern boolean grddead(struct monst *);
extern char vault_occupied(char *);
extern void invault(void);
extern int gd_move(struct monst *);
extern void paygd(void);
extern long hidden_gold(void);
extern boolean gd_sound(void);

/* ### version.c ### */

extern char *version_string(char *);
extern int doversion(void);
extern int doextversion(void);
extern boolean check_version(struct version_info *, const char *, boolean);
extern boolean uptodate(struct memfile*,const char *);
extern void store_version(int);

/* ### vision.c ### */

extern void vision_init(void);
extern int does_block(struct level *lev, int x, int y);
extern void vision_reset(void);
extern void vision_recalc(int);
extern void block_point(int,int);
extern void unblock_point(int,int);
extern boolean clear_path(int,int,int,int);
extern void do_clear_area(int,int,int, void (*)(int,int,void *),void *);

/* ### weapon.c ### */

extern boolean can_advance(int, boolean);
extern int hitval(struct obj *,struct monst *);
extern int dmgval(struct obj *,struct monst *);
extern struct obj *select_rwep(struct monst *);
extern struct obj *select_hwep(struct monst *);
extern void possibly_unwield(struct monst *,boolean);
extern int mon_wield_item(struct monst *);
extern int abon(void);
extern int dbon(void);
extern int enhance_weapon_skill(void);
extern int dump_skills(void);
extern void unrestrict_weapon_skill(int);
extern void use_skill(int,int);
extern void add_weapon_skill(int);
extern void lose_weapon_skill(int);
extern int weapon_type(struct obj *);
extern int uwep_skill_type(void);
extern int weapon_hit_bonus(struct obj *);
extern int weapon_dam_bonus(struct obj *);
extern void skill_init(const struct def_skill *);

/* ### were.c ### */

extern void were_change(struct monst *);
extern void new_were(struct monst *);
extern int were_summon(const struct permonst *,boolean,int *,char *);
extern void you_were(void);
extern void you_unwere(boolean);

/* ### wield.c ### */

extern void setuwep(struct obj *);
extern void setuqwep(struct obj *);
extern void setuswapwep(struct obj *);
extern int dowield(void);
extern int doswapweapon(void);
extern int dowieldquiver(void);
extern boolean wield_tool(struct obj *,const char *);
extern int can_twoweapon(void);
extern void drop_uswapwep(void);
extern int dotwoweapon(void);
extern void uwepgone(void);
extern void uswapwepgone(void);
extern void uqwepgone(void);
extern void untwoweapon(void);
extern void erode_obj(struct obj *,boolean,boolean);
extern int chwepon(struct obj *,int);
extern int welded(struct obj *);
extern void weldmsg(struct obj *);
extern void setmnotwielded(struct monst *,struct obj *);
extern void unwield_weapons_silently(void);

/* ### windows.c ### */

extern int getpos(coord *cc, boolean, const char *);
extern char yn_function(const char *query, const char *resp, char def);
extern int getdir(const char *, schar *dx, schar *dy, schar *dz);
extern char query_key(const char *query, int *count);
extern void getlin(const char *query, char *bufp);
extern int display_menu(struct nh_menuitem*, int, const char*, int, int*);
extern int display_objects(struct nh_objitem*, int, const char*, int, struct nh_objresult*);
extern boolean win_list_items(struct nh_objitem *items, int icount, boolean invent);

/* ### wizard.c ### */

extern void amulet(void);
extern int mon_has_amulet(struct monst *);
extern int mon_has_special(struct monst *);
extern int tactics(struct monst *);
extern void aggravate(void);
extern void clonewiz(void);
extern int pick_nasty(void);
extern int nasty(struct monst*);
extern void resurrect(void);
extern void intervene(void);
extern void wizdead(void);
extern void cuss(struct monst *);

/* ### worm.c ### */

extern int get_wormno(struct level *lev);
extern void initworm(struct monst *,int);
extern void worm_move(struct monst *);
extern void worm_nomove(struct monst *);
extern void wormgone(struct monst *);
extern void wormhitu(struct monst *);
extern void cutworm(struct monst *,xchar,xchar,struct obj *);
extern void see_wsegs(struct monst *);
extern void detect_wsegs(struct monst *,boolean);
extern void save_worm(int fd, struct level *lev, int mode);
extern void rest_worm(struct memfile *mf, struct level *lev);
extern void place_wsegs(struct monst *);
extern void remove_worm(struct monst *);
extern void place_worm_tail_randomly(struct monst *,xchar,xchar);
extern int count_wsegs(struct monst *);
extern boolean worm_known(const struct monst *);

/* ### worn.c ### */

extern void setworn(struct obj *,long);
extern void setnotworn(struct obj *);
extern void mon_set_minvis(struct monst *);
extern void mon_adjust_speed(struct monst *,int,struct obj *);
extern void update_mon_intrinsics(struct monst *,struct obj *,boolean,boolean);
extern int find_mac(struct monst *);
extern void m_dowear(struct monst *,boolean);
extern struct obj *which_armor(struct monst *,long);
extern void mon_break_armor(struct monst *,boolean);
extern void bypass_obj(struct obj *);
extern void clear_bypasses(void);
extern int racial_exception(struct monst *, struct obj *);

/* ### write.c ### */

extern int dowrite(struct obj *);

/* ### xmalloc.c ### */

extern void *xmalloc(int size);
extern void xmalloc_cleanup(void);

/* ### zap.c ### */

extern int bhitm(struct monst *,struct obj *);
extern void probe_monster(struct monst *);
extern boolean get_obj_location(struct obj *,xchar *,xchar *,int);
extern boolean get_mon_location(struct monst *,xchar *,xchar *,int);
extern struct monst *get_container_location(struct obj *obj, int *, int *);
extern struct monst *montraits(struct obj *,coord *);
extern struct monst *revive(struct obj *);
extern int unturn_dead(struct monst *);
extern boolean drain_item(struct obj *);
extern struct obj *poly_obj(struct obj *, int);
extern boolean obj_resists(struct obj *,int,int);
extern int bhito(struct obj *,struct obj *);
extern int bhitpile(struct obj *,int (*)(struct obj*,struct obj*),int,int);
extern int zappable(struct obj *);
extern void zapnodir(struct obj *);
extern int dozap(void);
extern int zapyourself(struct obj *,boolean);
extern boolean cancel_monst(struct monst *,struct obj *,
			       boolean,boolean,boolean);
extern void weffects(struct obj *, schar, schar, schar);
extern int spell_damage_bonus(void);
extern const char *exclam(int force);
extern void hit(const char *,struct monst *,const char *);
extern void miss(const char *,struct monst *);
extern struct monst *beam_hit(int,int,int,int,int (*)(struct monst*,struct obj*),
			     int (*)(struct obj*,struct obj*),struct obj *, boolean *);
extern struct monst *boomhit(int,int);
extern int burn_floor_paper(int,int,boolean,boolean);
extern void buzz(int,int,xchar,xchar,int,int);
extern void melt_ice(xchar,xchar);
extern int zap_over_floor(xchar,xchar,int,boolean *);
extern void fracture_rock(struct obj *);
extern boolean break_statue(struct obj *);
extern void destroy_item(int,int);
extern int destroy_mitem(struct monst *,int,int);
extern int resist(struct monst *,char,int,int);
extern void makewish(void);

#endif /* EXTERN_H */
