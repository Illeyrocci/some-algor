//COMMON QUEUE
class MyQueue {
public:
    int tail, head;
    vector<int> queue;
    MyQueue(int K_MAX) {//max_length of queue
        head = 0;
        tail = -1;
        queue.assign(K_MAX, 0);
    }
    void push(int x) {
        tail = (tail+1)%3;
        queue[tail] = x;
    }
    int pop() {
        int t = head;
        head = (head+1)%3;
        return queue[t];
    }
    int peek() {
        return queue[head];
    }
    bool empty() {
        return tail == head-1;
    }
};


//HAND-MADE PRIORITY QUEUE of pairs with consistent map (priority <-> object_id).
void heap_push(vector<pair<int, int>>& heap, pair<int, int> x, map<int, int> &sec_pos){
    int pos = (int) heap.size();
    heap.push_back(x);
    sec_pos[x.second] = pos; 
    while (pos > 0 && heap[pos].first < heap[(pos-1)/2].first){
        sec_pos[heap[pos].second] = (pos-1)/2;
        sec_pos[heap[(pos-1)/2].second] = pos;
        swap(heap[pos], heap[(pos-1)/2]);
        pos = (pos-1)/2;   
    }
}

void heap_erase(vector<pair<int ,int>>& heap, map<int, int>& sec_pos){
    int64_t isz = (int) heap.size();
    sec_pos[heap[isz-1].second] = 0;
    sec_pos.erase(heap[0].second);
    heap[0] = heap[isz - 1];
    int i = 0;
    while (i*2+2 < isz){
        int min_son_index = 2*i + 1;
        if (heap[i*2+2].first < heap[min_son_index].first) min_son_index = i*2+2;
        if (heap[i].first > heap[min_son_index].first){
                
            sec_pos[heap[i].second] = min_son_index;
            sec_pos[heap[min_son_index].second] = i;
            swap(heap[i], heap[min_son_index]);
            i = min_son_index;
        }
        else break;
    }
    heap.pop_back();
}

void heap_change(vector<pair<int, int>> & heap, map<int, int>& sec_pos, int nov, int target){
    int pos = sec_pos[target];
    heap[pos] = make_pair(nov, target);
    while (pos > 0 && heap[(pos-1)/2].first > heap[pos].first){
        sec_pos[heap[pos].second] = (pos-1)/2;
        sec_pos[heap[(pos-1)/2].second] = pos;
        swap(heap[(pos-1)/2], heap[pos]);

        pos = (pos-1)/2;
    }
    int isz = (int) heap.size();
    while (1){
        int child1 = 2*pos + 1;
        int child2 = 2*pos + 2;
        if (child1 < isz && child2 < isz){
            if(heap [child1].first >= heap[child2].first && heap[child2].first < heap[pos].first) {
                sec_pos[heap[pos].second] = child2;
                sec_pos[heap[child2].second] = pos;
                swap(heap[pos], heap[child2]);
                pos = child2;
            }
            else if (heap [child1].first <= heap[child2].first && heap[child1].first< heap[pos].first){
                sec_pos[heap[pos].second] = child1;
                sec_pos[heap[child1].second] = pos;
                swap(heap[pos], heap[child1]);
                pos = child1;
            }
            else{
                break;
            }
        } 
        else if (child1 < isz && child2 >= isz){
            if(heap[child1].first < heap[pos].first) {
                sec_pos[heap[pos].second] = child1;
                sec_pos[heap[child1].second] = pos;
                swap(heap[pos], heap[child1]);
                pos = child1;
            }
            else break;
        }
        else if (child2 < isz && child1 >= isz){
            if(heap[child2] < heap[pos]) {
                sec_pos[heap[pos].second] = child2;
                sec_pos[heap[child2].second] = pos;
                swap(heap[pos], heap[child2]);
                pos = child2;
            }
            else break;
        }
        else break;
    }
}





//
