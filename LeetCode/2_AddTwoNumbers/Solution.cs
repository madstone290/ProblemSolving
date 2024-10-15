/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     public int val;
 *     public ListNode next;
 *     public ListNode(int val=0, ListNode next=null) {
 *         this.val = val;
 *         this.next = next;
 *     }
 * }
 */
public class Solution
{
    /**
    * 두 노드의 값을 더하여 1의 자리를 새로운 연결리스트에 추가한다.
    * 캐리값이 있으면 다음 계산에 더해준다.
    */
    public ListNode AddTwoNumbers(ListNode l1, ListNode l2)
    {
        ListNode current = new();
        ListNode answer = current;
        int carry = 0;
        int value = 0;
        while (l1 != null || l2 != null)
        {
            int l1Val = l1?.val ?? 0;
            int l2Val = l2?.val ?? 0;
            int sum = l1Val + l2Val + carry;
            carry = sum / 10;
            value = sum % 10;

            current.val = value;
            if (l1?.next == null && l2?.next == null)
            {
                if (carry > 0)
                {
                    current.next = new ListNode(carry);
                }
            }
            else
            {
                current.next = new ListNode();
            }

            current = current.next;
            l1 = l1?.next;
            l2 = l2?.next;
        }



        return answer;
    }
}


