import java.util.ArrayList;

public class CengTreeNodeInternal extends CengTreeNode
{
    private ArrayList<Integer> keys;
    private ArrayList<CengTreeNode> children;

    public CengTreeNodeInternal(CengTreeNode parent)
    {
        super(parent);

        // TODO: Extra initializations, if necessary.
        keys = new ArrayList<Integer>();
        children = new ArrayList<CengTreeNode>();

        this.type = CengNodeType.Internal;
    }

    // GUI Methods - Do not modify
    public ArrayList<CengTreeNode> getAllChildren()
    {
        return this.children;
    }
    public Integer keyCount()
    {
        return this.keys.size();
    }
    public Integer keyAtIndex(Integer index)
    {
        if(index >= this.keyCount() || index < 0)
        {
            return -1;
        }
        else
        {
            return this.keys.get(index);
        }
    }

    // Extra Functions
    public CengTreeNode getChildAt(Integer index) {
        return this.children.get(index);
    }

    public void insertKey(Integer index, Integer key)
    {
        keys.add(index,key);
    }

    public void appendKey(Integer key)
    {
        keys.add(key);
    }

    public void insertChild(Integer index, CengTreeNode child)
    {
        children.add(index,child);
    }

    public void appendChild(CengTreeNode child)
    {
        children.add(child);
    }

    public ArrayList<Integer> getKeys()
    {
        return this.keys;
    }

    public void setChild(Integer index, CengTreeNode child)
    {
        children.set(index,child);
    }
}
