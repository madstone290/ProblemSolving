List<int> l1 = [9, 9, 9, 9, 9, 9, 9];
List<int> l2 = [9, 9, 9, 9];

ListNode node1 = new ();
ListNode node2 = new ();

ListNode node1Next = node1;
ListNode node2Next = node2;

// 노드에 숫자 채우기
for(int i = 0; i < l1.Count; i++)
{
    node1Next.val = l1[i];
    if (i != l1.Count - 1)
    {
        node1Next.next = new ListNode();
        node1Next = node1Next.next;
    }
}

for (int i = 0; i < l2.Count; i++)
{
    node2Next.val = l1[i];
    if (i != l1.Count - 1)
    {
        node2Next.next = new ListNode();
        node2Next = node2Next.next;
    }
}
var answer = new Solution().AddTwoNumbers(node1, node2);

while (answer != null)
{
    Console.WriteLine(answer.val);
    answer = answer.next;
}