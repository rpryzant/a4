/*
 * Utility routines supporting the Williams Unary File System
 * (c) the Great Class of 2016, especially Tony Liu and Reid Pryzant
 */
#include <linux/types.h>                                                                             
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wufs_fs.h"
#include "wufs.h"

/*
 * Compute (rounding up) chunks of size chunkSize needed to hold size items.
 * Might be used to find out how many blocks we need for i inodes:
 *    fullChunks(i,WUFS_BLOCKSIZE/WUFS_INODESIZE);
 */
int fullChunks(int size, int chunkSize)
{
  return (size + (chunkSize-1))/chunkSize;
}

/*
 * Some bitfield manipulation functions
 * Accidentally deleted (*sigh*) by Duane.
 */

/*
 * Set the ith bit (zero origin) in bitfield f
 */
void setBit(__u8 *f, int i)
{
  f[i/8] |= 1<<(i%8);
}

/*
 * Clear the ith bit (zero origin) in bitfield f
 */
void clearBit(__u8 *f, int i)
{
  f[i/8] &= ~(1<<(i%8));
}

/*
 * Return the ith bit (zero origin) in bitfield field: 0 or 1
 */
int getBit(__u8 *f, int i)
{
  if (1<<(i%8) & f[i/8]) return 1;
  else                   return 0;

}

/*
 * Find the next bit (starting with i or, if -1, 0) set in field of n.
 * If none, return -1.
 */
int findNextSet(__u8 *f, int i, int n)
{
  if(i<0) i = 0;
  while (i <= n) {
    if (getBit(f, i)) return i;
    i++;
  }
  return -1;
}

/*
 * Find the next bit (starting with i or, if -1, 0) clear in field of n.
 * If none, return -1.
 */
int findNextClear(__u8 *f, int i, int n)
{
  if(i<0) i = 0;
  while (i <= n) {
    if (!getBit(f, i)) return i;
    i++;
  }
  return -1;
}


