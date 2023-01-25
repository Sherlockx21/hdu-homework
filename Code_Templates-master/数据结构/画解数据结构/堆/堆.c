#include <malloc.h>

#define bool int 
#define false 0
#define true 1
 
/**********************************С����ģ��************************************/
#define lson(idx) (idx << 1|1)
#define rson(idx) ((idx + 1) << 1)
#define parent(idx) ((idx - 1) >> 1)
#define root 0

typedef struct {
    int key;
    void *any; 
}DataType;

// -1 �� 1 �������ͱ���˴󶥶�
int compareData(const DataType* a, const DataType* b) {
    if(a->key < b->key) {
        return -1;
    }else if(a->key > b->key) {
        return 1;
    }
    return 0;
}
void swap(DataType* a, DataType* b) {
    DataType tmp = *a;
    *a = *b;
    *b = tmp;
}

typedef struct {
    DataType *data;
    int size;
    int capacity;
}Heap;

// �ڲ��ӿڣ�Сд�շ�

// heapShiftDown ����ӿ���һ���ڲ��ӿڣ�������Сд�շ����֣����ڶԶ���Ԫ�ؽ���ɾ����ʱ����³�������
void heapShiftDown(Heap* heap, int curr) {
    int son = lson(curr);

    while(son < heap->size) {
        if( rson(curr) < heap->size ) {
            if( compareData( &heap->data[rson(curr)], &heap->data[son] ) < 0 ) {
                son = rson(curr);                        // (1) ʼ��ѡ��ֵ��С�Ľ��
            }        
        }
        if( compareData( &heap->data[son], &heap->data[curr] ) < 0 ) {
            swap(&heap->data[son], &heap->data[curr]);   // (2) �ӽ���ֵС�ڸ���㣬��ִ�н�����
            curr = son;
            son = lson(curr);
        }else {
            break;                                       // (3) �ӽ���ֵ���ڸ���㣬˵���Ѿ���ȷ��λ���³���������������ѭ����
        }
    }
}

// heapShiftUp ����ӿ���һ���ڲ��ӿڣ�������Сд�շ����֣����ڶԶ���Ԫ�ؽ��в����ʱ����ϸ�������
void heapShiftUp(Heap* heap, int curr) {
    int par = parent(curr);
    while(par >= root) {
        if( compareData( &heap->data[curr], &heap->data[par] ) < 0 ) {
            swap(&heap->data[curr], &heap->data[par]);   // (1) �ӽ���ֵС�ڸ���㣬��ִ�н�����
            curr = par;
            par = parent(curr);
        }else {
            break;                                       // (2) �ӽ���ֵ���ڸ���㣬˵���Ѿ���ȷ��λ���ϸ���������������ѭ����
        }
    }
}

bool heapIsFull(Heap *heap) {
    return heap->size == heap->capacity;
}

// �ⲿ�ӿڣ���д�շ�

// �ѵ��п�
bool HeapIsEmpty(Heap *heap) {
    return heap->size == 0;
}

// �ѵĲ���
// �嵽���һ��λ�ã�Ȼ�󲻶Ͻ����ϸ�����
bool HeapPush(Heap* heap, DataType data) {
    if( heapIsFull(heap) ) {
        return false;
    }
    heap->data[ heap->size++ ] = data;
    heapShiftUp(heap, heap->size-1);
    return true;
}


// �ѵ�ɾ��
// 1��ɾ���Ѷ�Ԫ��ʱ�����ѵײ����±�����Ԫ�ط���Զ���
// 2��Ȼ����� shiftDown �����Ԫ�ؽ����³�������
// ����С������˵���Ӹ���Ҷ�ӵ�·����Ȼ�ǵ��������ģ������³�����һ������ֹ��·����ĳ���㣬���ұ�֤���еĶ�·�������ܹ�ά�ֵ���������
bool HeapPop(Heap *heap) {
    if(HeapIsEmpty(heap)) {
        return false;
    }
    heap->data[root] = heap->data[ --heap->size ];
    heapShiftDown(heap, root);
    return true;
}

DataType HeapTop(Heap *heap) {
    // assert(!HeapIsEmpty(heap));
    return heap->data[root];
}

// ������
Heap* HeapCreate(DataType *data, int dataSize, int maxSize) {
    int i;
    Heap *h = (Heap *)malloc( sizeof(Heap) );
    
    h->data = (DataType *)malloc( sizeof(DataType) * maxSize );
    h->size = 0;
    h->capacity = maxSize;

    for(i = 0; i < dataSize; ++i) {
        HeapPush(h, data[i]);
    }
    return h;
}

// ���ٶ�
void HeapFree(Heap *heap) {
    free(heap->data);
    free(heap);
}

/**********************************С����ģ��************************************/













