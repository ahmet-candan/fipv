/*
* IPv4 validator functions definition.
*
* Function: is_ipv4
* ----------------------------
* Returns true if given string is a IPv4 otherwise false.
*
* ipv4_addr: target string to be validated (char *)
* returns: true if given address is a IPv4 address (bool)
*
* Function: is_ipv4_cidr
* ----------------------------
* Returns true if given string is a IPv4CIDR otherwise false.
*
* ipv4_addr_cidr: target string to be validated (char *)
* returns: true if given address is a IPv4CIDR (bool)
*/

#ifndef _IPV4_H_
#define _IPV4_H_

#define IPV4_DELIMITER "."
#define IP_CIDR_DELIMITER "/"

#include "split.h"
#include "utils.h"

bool is_ipv4(char *ipv4_addr);
bool is_ipv4_cidr(char *ipv4_addr_cidr);

bool is_ipv4(char *ipv4_addr) {
    struct split_t splitted = split(ipv4_addr, IPV4_DELIMITER);

    if (splitted.length != 4)
      return free_split_r(&splitted, false);

    for (size_t i = 0; i < splitted.length; i++) {
        char *part = splitted.tokens[i];

        if (!is_digit(part))
          return free_split_r(&splitted, false);

        if (!(0 <= atoi(part) && atoi(part) < 256))
          return free_split_r(&splitted, false);
    }

  return free_split_r(&splitted, true);
}

bool is_ipv4_cidr(char *ipv4_addr_cidr) {
    struct split_t splitted = split(ipv4_addr_cidr, IP_CIDR_DELIMITER);

    if (splitted.length != 2)
      return free_split_r(&splitted, false);

    char *prefix = splitted.tokens[0];
    char *suffix = splitted.tokens[1];

    if (!is_ipv4(prefix) || !is_digit(suffix))
      return free_split_r(&splitted, false);

    if (!(0 <= atoi(suffix) && atoi(suffix) <= 32))
      return free_split_r(&splitted, false);

    return free_split_r(&splitted, true);
}

#endif
