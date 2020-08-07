#include "dev.h"
#include "enx_freertos.h"

#include <string.h> // for strcpy, strlen, memcpy, memset
#include "videnc_heap.h"

#if (LOAD_FS_SDCARD==1)

#define encHeap_filename_cmp_offset	(4) // 4(byte): NOR_, EVT_�� ���� �� 4���ڴ� ������ �ʴ´�.
#define encHeap_getParent(idx)		((int)(((idx)-1)/2))
#define encHeap_getLeftChild(idx)	((int)(2*(idx))+1)

ENX_OKFAIL encHeap_create(encHeap* h, int capacity)
{
  h->capacity = capacity;
  h->usedsize = 0;
  h->node = (encHData*)pvPortCalloc(sizeof(encHData), h->capacity);
  if (h->node) {
    return ENX_OK;
  } else {
    return ENX_FAIL;
  }
}

void encHeap_destroy(encHeap* h)
{
  if (h->node) {
    vPortFree(h->node);
    h->node = NULL;
  }
}

static void encHeap_swapNode(encHeap* h, int idx1, int idx2)
{
  encHData temp;
  memcpy(&temp, &h->node[idx1], sizeof(encHData));
  memcpy(&h->node[idx1], &h->node[idx2], sizeof(encHData));
  memcpy(&h->node[idx2], &temp, sizeof(encHData));
}

static void encHeap_deQueue(encHeap* h, encHData* root) 
{
  // ������ ������ ����
  if (h->usedsize == 0) {
    memset(root, 0, sizeof(encHData));
    return;
  }

  int parentPos = 0, leftPos, rightPos, selectChild;
  memcpy(root, &h->node[0], sizeof(encHData));
  memset(&h->node[0], 0, sizeof(encHData));
  h->usedsize--;
  encHeap_swapNode(h, 0, h->usedsize);
  leftPos = encHeap_getLeftChild(0);
  rightPos = leftPos + 1;
  while (1) {
    selectChild = 0;
    if (leftPos >= h->usedsize) {
      break;
    }

    if (rightPos >= h->usedsize) {
      selectChild = leftPos;
    } else {
      if(strcmp(h->node[leftPos].filename+encHeap_filename_cmp_offset, h->node[rightPos].filename+encHeap_filename_cmp_offset) > 0) {
        selectChild = rightPos;
      } else {
        selectChild = leftPos;
      }
    } 

    if (strcmp(h->node[selectChild].filename+encHeap_filename_cmp_offset, h->node[parentPos].filename+encHeap_filename_cmp_offset) < 0) {
      encHeap_swapNode(h, parentPos, selectChild);
      parentPos = selectChild;
    } else {
      break;
    }
    leftPos = encHeap_getLeftChild(parentPos);
    rightPos = leftPos + 1;
  }
}

static int encHeap_enQueue(encHeap* h, encHData data)
{
  int currentPos, parentPos, deletereturn = 0;

  // �����ִ� ������ ������
  if (h->usedsize == h->capacity) {
    deletereturn = 1;	// ������ ������ ����
    if (strcmp(h->node->filename+encHeap_filename_cmp_offset, data.filename+encHeap_filename_cmp_offset) > 0) {
      // ���� ���� data.filename�� �����ؾ� �Ѵ�. ���� �� �� ���� ����.
      memcpy(&h->delHData, &data, sizeof(encHData));
      printf("delete1 %s\n", data.filename);
      return deletereturn;
    } else {
      // ������ heap ������ �� ���� ������ filename�� �����Ѵ�. �׸��� ���� data.filename�� �߰��Ѵ�.
      encHData temp;
      encHeap_deQueue(h, &temp);
      memcpy(&h->delHData, &temp, sizeof(encHData));
      printf("delete2 %s\n", temp.filename);
    }
  }

  currentPos = h->usedsize;
  parentPos = encHeap_getParent(currentPos);

  memcpy(&h->node[currentPos], &data, sizeof(encHData));

  while (currentPos > 0 && strcmp(h->node[currentPos].filename+encHeap_filename_cmp_offset, h->node[parentPos].filename+encHeap_filename_cmp_offset) < 0) {
    encHeap_swapNode(h, currentPos, parentPos);
    currentPos = parentPos;
    parentPos = encHeap_getParent(currentPos);
  }
  h->usedsize++;

  return deletereturn;
}

void encHeap_resetQueue(encHeap* h)
{
  h->usedsize = 0;
  memset((void *)h->node, 0, sizeof(encHData) * h->capacity);
}

void encHeap_deleteQueue(encHeap* h, char* filename)
{
  encHData temp;
  encHeap_deQueue(h, &temp);
  if(strlen(temp.filename) != 0) {
    strcpy(filename, temp.filename);
  } else {
    filename[0] = '\0';
  }
}

int encHeap_addQueue(encHeap* h, char* filename)
{
  encHData temp;
  strcpy(temp.filename, filename);
  return encHeap_enQueue(h, temp);
}

#endif
