import java.util.ArrayList;
import java.util.Stack;

public class CengTree
{
    public static CengTreeNode root;
    // Any extra attributes...

    public CengTree(Integer order)
    {
        CengTreeNode.order = order;
        // TODO: Initialize the class
        root = new CengTreeNodeLeaf(null);
    }

    public static void addBook(CengBook book)
    {
        // TODO: Insert Book to Tree
        CengTreeNodeLeaf nodeToBeInserted = indexOf(book.getBookID());
        ArrayList<CengBook> booksOfNewNode = nodeToBeInserted.getBooks();

        int indexToInsert = findIndexToInsert(nodeToBeInserted, booksOfNewNode, book);
        nodeToBeInserted.insertBook(indexToInsert, book);

        if (nodeToBeInserted.bookCount() == (2 * CengTreeNode.order) + 1)
        {
            if (nodeToBeInserted.getParent() == null)
                handleOverflowOfRoot(nodeToBeInserted);
            else
                handleOverflowOfNode(nodeToBeInserted);
        }
    }

    public static ArrayList<CengTreeNode> searchBook(Integer bookID)
    {
        // TODO: Search within whole Tree, return visited nodes.
        // Return null if not found.
        ArrayList<CengTreeNode> res = new ArrayList<CengTreeNode>();

        if (!exists(bookID))
        {
            System.out.println("Could not find " + bookID + ".");
            return res;
        }

        CengTreeNode node = root;
        boolean flag;
        int initialLevel;
        int level=0;
        String tabs="";
        while (node.getType() == CengNodeType.Internal)
        {
            initialLevel = level;
            tabs = "";
            while (level > 0)
            {
                tabs += "\t";
                level--;
            }

            System.out.println(tabs + "<index>");
            for (int i = 0; i < ((CengTreeNodeInternal) node).keyCount(); i++)
            {
                System.out.println(tabs + ((CengTreeNodeInternal) node).keyAtIndex(i));
                res.add(node);
            }
            System.out.println(tabs + "</index>");

            flag = false;
            for (int i = 0; i < ((CengTreeNodeInternal) node).keyCount(); i++)
            {
                if (((CengTreeNodeInternal) node).keyAtIndex(i) > bookID)
                {
                    node = ((CengTreeNodeInternal) node).getChildAt(i);
                    flag = true;
                    break;
                }
            }
            if (!flag)
                node = ((CengTreeNodeInternal) node).getChildAt(((CengTreeNodeInternal) node).keyCount());

            level = initialLevel+1;
        }

        tabs += "\t";

        for (int i = 0; i < ((CengTreeNodeLeaf) node).bookCount(); i++)
        {
            if (((CengTreeNodeLeaf) node).bookKeyAtIndex(i).equals(bookID))
            {
                System.out.print(tabs + "<record>");
                System.out.print(((CengTreeNodeLeaf) node).bookAt(i).getBookID());
                System.out.print("|");
                System.out.print(((CengTreeNodeLeaf) node).bookAt(i).getBookTitle());
                System.out.print("|");
                System.out.print(((CengTreeNodeLeaf) node).bookAt(i).getAuthor());
                System.out.print("|");
                System.out.print(((CengTreeNodeLeaf) node).bookAt(i).getGenre());
                System.out.print("</record>\n");
                res.add(node);
            }
        }

        return res;
    }

    public static void printTree()
    {
        // TODO: Print the whole tree to console
        Stack<CengTreeNode> s = new Stack<CengTreeNode>();
        s.add(root);

        int level;
        String tabs;
        while (!s.isEmpty())
        {
            CengTreeNode node = s.pop();
            level = node.getHeight();
            tabs = "";
            while (level > 0)
            {
                tabs += "\t";
                level--;
            }

            if (node.getType() == CengNodeType.Internal)
            {
                ArrayList<CengTreeNode> children = ((CengTreeNodeInternal) node).getAllChildren();
                for (int i = children.size() - 1; i >= 0; i--)
                    s.add(children.get(i));

                System.out.println(tabs + "<index>");
                for (int i = 0; i < ((CengTreeNodeInternal) node).keyCount(); i++)
                    System.out.println(tabs + ((CengTreeNodeInternal) node).keyAtIndex(i));
                System.out.println(tabs + "</index>");
            }

            else if (node.getType() == CengNodeType.Leaf && ((CengTreeNodeLeaf) node).bookCount() > 0)
            {
                System.out.println(tabs + "<data>");
                for (int i = 0; i < ((CengTreeNodeLeaf) node).bookCount(); i++)
                {
                    System.out.print(tabs + "<record>");
                    System.out.print(((CengTreeNodeLeaf) node).bookAt(i).getBookID());
                    System.out.print("|");
                    System.out.print(((CengTreeNodeLeaf) node).bookAt(i).getBookTitle());
                    System.out.print("|");
                    System.out.print(((CengTreeNodeLeaf) node).bookAt(i).getAuthor());
                    System.out.print("|");
                    System.out.print(((CengTreeNodeLeaf) node).bookAt(i).getGenre());
                    System.out.print("</record>\n");
                }
                System.out.println(tabs + "</data>");
            }
        }
    }

    // Any extra functions...
    public static CengTreeNodeLeaf indexOf(Integer key)
    {
        CengTreeNode node = root;
        boolean flag;

        while (node.getType() == CengNodeType.Internal)
        {
            flag = false;
            for (int i = 0; i < ((CengTreeNodeInternal) node).keyCount(); i++)
            {
                if (((CengTreeNodeInternal) node).keyAtIndex(i) > key)
                {
                    node = ((CengTreeNodeInternal) node).getChildAt(i);
                    flag = true;
                    break;
                }
            }
            if (!flag)
                node = ((CengTreeNodeInternal) node).getChildAt(((CengTreeNodeInternal) node).keyCount());
        }

        return ((CengTreeNodeLeaf) node);
    }

    public static boolean exists(Integer bookID)
    {
        CengTreeNode node = root;

        boolean flag;
        while (node.getType() == CengNodeType.Internal)
        {
            flag = false;
            for (int i = 0; i < ((CengTreeNodeInternal) node).keyCount(); i++)
            {
                if (((CengTreeNodeInternal) node).keyAtIndex(i) > bookID)
                {
                    node = ((CengTreeNodeInternal) node).getChildAt(i);
                    flag = true;
                    break;
                }
            }
            if (!flag)
                node = ((CengTreeNodeInternal) node).getChildAt(((CengTreeNodeInternal) node).keyCount());
        }

        for (int i = 0; i < ((CengTreeNodeLeaf) node).bookCount(); i++)
        {
            if (((CengTreeNodeLeaf) node).bookKeyAtIndex(i).equals(bookID))
                return true;
        }

        return false;
    }

    public static void handleOverflowOfRoot(CengTreeNodeLeaf nodeToBeInserted)
    {
        CengTreeNodeInternal newRoot = new CengTreeNodeInternal(null);
        CengTreeNodeLeaf newNode = new CengTreeNodeLeaf(newRoot);
        int index = CengTreeNode.order;
        int bookCount = nodeToBeInserted.bookCount();

        for (int j = 0; index < bookCount; j++)
            newNode.insertBook(j, nodeToBeInserted.bookAt(index++));

        nodeToBeInserted.getBooks().subList(CengTreeNode.order, nodeToBeInserted.getBooks().size()).clear();
        nodeToBeInserted.setParent(newRoot);
        newRoot.insertKey(0, newNode.bookAt(0).getBookID());
        newRoot.insertChild(0, nodeToBeInserted);
        newRoot.insertChild(1, newNode);
        root = newRoot;
    }

    public static int findIndexToInsert(CengTreeNodeLeaf nodeToBeInserted, ArrayList<CengBook> booksOfNewNode, CengBook book)
    {
        int bookCount = nodeToBeInserted.bookCount();
        int indexToInsert = -1;

        for (int i = 0; i < bookCount; i++)
        {
            if (booksOfNewNode.get(i).getBookID() > book.getBookID())
            {
                indexToInsert = i;
                break;
            }
        }
        if (indexToInsert == -1)
            return bookCount;

        return indexToInsert;
    }

    public static void handleOverflowOfNode(CengTreeNodeLeaf nodeToBeInserted)
    {
        CengTreeNode parent = nodeToBeInserted.getParent();
        CengTreeNodeLeaf newNode = new CengTreeNodeLeaf(parent);
        int bookCount = nodeToBeInserted.bookCount();

        for (int index = CengTreeNode.order, j = 0; index < bookCount; index++,j++)
            newNode.insertBook(j,nodeToBeInserted.bookAt(index));

        nodeToBeInserted.getBooks().subList(CengTreeNode.order, nodeToBeInserted.getBooks().size()).clear();
        addChildToParent(newNode, parent);
        handleOverflowOfInternal(parent);
    }

    public static void addChildToParent(CengTreeNodeLeaf newNode, CengTreeNode parent)
    {
        int key = newNode.bookKeyAtIndex(0);
        int keyCount = ((CengTreeNodeInternal) parent).keyCount();
        boolean flag = false;

        for (int i = 0; i < keyCount; i++)
        {
            if (((CengTreeNodeInternal) parent).keyAtIndex(i) > key)
            {
                ((CengTreeNodeInternal) parent).insertKey(i, key);
                ((CengTreeNodeInternal) parent).insertChild(i + 1, newNode);
                flag = true;
                break;
            }
        }

        if (!flag)
        {
            ((CengTreeNodeInternal) parent).appendKey(key);
            ((CengTreeNodeInternal) parent).appendChild(newNode);
        }
    }

    public static void handleOverflowOfInternal(CengTreeNode parent)
    {
        CengTreeNode grandParent;

        while (((CengTreeNodeInternal) parent).keyCount() == (2 * CengTreeNode.order) + 1)
        {
            grandParent = parent.getParent();

            if (grandParent == null)
            {
                handleOverflowOfInternalWithoutParent(parent);
                break;
            }

            else
            {
                handleOverflowOfInternalWithParent(parent, grandParent);
                parent = grandParent;
            }
        }
    }

    public static void handleOverflowOfInternalWithoutParent(CengTreeNode parent)
    {
        CengTreeNodeInternal newRoot = new CengTreeNodeInternal(null);
        CengTreeNodeInternal newInternalNode = new CengTreeNodeInternal(newRoot);
        int index = CengTreeNode.order+1;
        int keyCount = ((CengTreeNodeInternal) parent).keyCount();

        for (int j = 0; index < keyCount; j++)
        {
            newInternalNode.insertKey(j,((CengTreeNodeInternal) parent).keyAtIndex(index));
            newInternalNode.insertChild(j,((CengTreeNodeInternal) parent).getChildAt(index));
            ((CengTreeNodeInternal) parent).getChildAt(index).setParent(newInternalNode);
            index++;
        }

        newInternalNode.insertChild(newInternalNode.keyCount(),((CengTreeNodeInternal) parent).getChildAt(((CengTreeNodeInternal) parent).keyCount()));
        ((CengTreeNodeInternal) parent).getChildAt(((CengTreeNodeInternal) parent).keyCount()).setParent(newInternalNode);

        int key = ((CengTreeNodeInternal) parent).keyAtIndex(CengTreeNode.order);
        ((CengTreeNodeInternal) parent).getKeys().subList(CengTreeNode.order, ((CengTreeNodeInternal) parent).getKeys().size()).clear();
        ((CengTreeNodeInternal) parent).getAllChildren().subList(CengTreeNode.order + 1, ((CengTreeNodeInternal) parent).getAllChildren().size()).clear();
        newRoot.insertKey(0, key);
        newRoot.insertChild(0, parent);
        parent.setParent(newRoot);
        newRoot.insertChild(1, newInternalNode);
        root = newRoot;
    }

    public static void handleOverflowOfInternalWithParent(CengTreeNode parent, CengTreeNode grandParent)
    {
        CengTreeNodeInternal newInternalNode = new CengTreeNodeInternal(grandParent);
        int index = CengTreeNode.order + 1;
        int keyCount = ((CengTreeNodeInternal) parent).keyCount();
        boolean flag = false;

        for (int j = 0; index < keyCount; j++)
        {
            newInternalNode.insertKey(j,((CengTreeNodeInternal) parent).keyAtIndex(index));
            newInternalNode.insertChild(j,((CengTreeNodeInternal) parent).getChildAt(index));
            ((CengTreeNodeInternal) parent).getChildAt(index).setParent(newInternalNode);
            index++;
        }

        newInternalNode.insertChild(newInternalNode.keyCount(),((CengTreeNodeInternal) parent).getChildAt(((CengTreeNodeInternal) parent).keyCount()));
        ((CengTreeNodeInternal) parent).getChildAt(((CengTreeNodeInternal) parent).keyCount()).setParent(newInternalNode);

        int key = ((CengTreeNodeInternal) parent).keyAtIndex(CengTreeNode.order);
        ((CengTreeNodeInternal) parent).getKeys().subList(CengTreeNode.order, ((CengTreeNodeInternal) parent).getKeys().size()).clear();
        ((CengTreeNodeInternal) parent).getAllChildren().subList(CengTreeNode.order + 1, ((CengTreeNodeInternal) parent).getAllChildren().size()).clear();

        keyCount = ((CengTreeNodeInternal) grandParent).keyCount();
        for (int i = 0; i < keyCount; i++)
        {
            if (((CengTreeNodeInternal) grandParent).keyAtIndex(i) > key)
            {
                ((CengTreeNodeInternal) grandParent).insertKey(i, key);
                ((CengTreeNodeInternal) grandParent).insertChild(i, parent);
                ((CengTreeNodeInternal) grandParent).setChild(i + 1, newInternalNode);
                flag = true;
                break;
            }
        }

        if (!flag)
        {
            ((CengTreeNodeInternal)grandParent).appendKey(key);
            ((CengTreeNodeInternal)grandParent).appendChild(newInternalNode);
        }
    }
}
