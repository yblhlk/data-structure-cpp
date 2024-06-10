模板单链表如何写：
1. Node设计为内部类的原因：用同一个模板。（但是好像不是同一个也没什么问题。）
2. createNode() : 使用new来创建Node对象，才能不随着函数消亡。
3. insert() : 头插要改变_head的指向，所以index==0时要单独考虑。
4. erase() : 头删要改变_head的指向，所以index==0时要单独考虑。
小细节：
为什么插入和删除时没单独考虑size==0的情况？
erase() 中 if(index >= size || index < 0) 在 else if(index == 0)前面，
这样当没有节点时即size==0时被一并处理掉了。insert() 中也是同样的考虑。