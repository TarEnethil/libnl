#include <linux/if.h>
#include <linux/rtnetlink.h>
#include <netlink/msg.h>
#include <netlink/netlink.h>
#include <netlink/route/link.h>
#include <netlink/route/rtnl.h>

int main() {
    struct rtnl_link *link = NULL;
    struct rtnl_link *req = NULL;
    struct nl_sock *sk = NULL;
    struct nl_cache *link_cache = NULL;

    sk = nl_socket_alloc();
    nl_connect(sk, NETLINK_ROUTE);
   
    rtnl_link_alloc_cache(sk, AF_INET6, &link_cache);
    link = rtnl_link_get_by_name(link_cache, "libnl-tun");

    req = rtnl_link_alloc();
    rtnl_link_set_flags(req, IFF_UP);
	
    /* segfault */
    rtnl_link_change(sk, link, req, 0);
    
    rtnl_link_put(link);
    rtnl_link_put(req);
    nl_cache_free(link_cache);
    nl_socket_free(sk);

    return 0;
}

/*
 * #0  0x0000000000000000 in ?? ()
 * #1  0x00007ffff7f6a1c4 in af_request_type (changes=0x55555555bb30, af_type=10) at lib/route/link.c:118
 * #2  rtnl_link_build_change_request (orig=<optimized out>, changes=0x55555555bb30, flags=0, result=result@entry=0x7fffffffdff8) at lib/route/link.c:1744
 * #3  0x00007ffff7f6a2a4 in rtnl_link_change (sk=0x555555559930, orig=<optimized out>, changes=<optimized out>, flags=<optimized out>) at lib/route/link.c:1793
 * #4  0x0000555555555266 in main () at main.cpp:24
 * /
