public class Solution
{
    public int[] TwoSum(int[] nums, int target)
    {
        // Key: number, Value: index
        Dictionary<int, int> numberMap = new();
        for (int i = 0; i < nums.Length; i++)
        {
            int complement = target - nums[i];
            if (numberMap.ContainsKey(complement))
            {
                return new int[] { numberMap[complement], i };
            }
            numberMap[nums[i]] = i;
        }

        return new int[] { };
    }
}