DeleteIndex(){
	block = FindLeafBlock(index root, key);
	DeleteEntry(block, key);
}

DeleteEntry(block, key){
	delete the key from the node; --> DeleteKey(block, key);
	
	// remove the root
	if(block.isRoot && block.num == 1){
		child = block.data[0];
		child.isRoot = TRUE;
		child.parent = -1;
		FreeBlock(child);

		return;
	}
	
	// nothing to adjust
	if(the node has at least the minimum number([(cap+1)/2]) || block.isRoot)
		return;

	// borrow an entry from left
	// TODO consider the nonleaf
	offset = FindKeyInNonleaf(parent, key);
	left = the left sibling block;
	if(left has more than [(cap+1)/2] data){
		increase the num of the block;
		RightShiftLeaf(block, num - 1, 1);
		store the last data of left into the node at first place;
		DeleteKey(left, newKey);

		UpdateKey(parent, oldKey(second), newKey(first));

		return;
	}

	// borrow an entry from right
	// TODO consider the nonleaf
	right = the right sibling block;
	if(right has more than [(cap+1)/2] data){
		UpdateKey(right\'s Parent, oldKey(first), newKey(second));
		increse the num of the block;
		store the first data of right into the node at last palace;
		DeleteKey(right, oldKey);

		return;
	}

	// coalesce the block to the left
	if(left != -1){
		copy the data from block to the left;
		adjust the next blockId;
		adjust the chidren\'s parent blockId;
		DeleteBlock(block);

		DeleteEntry(left.parent, key);
	}

	// coalesce the block to the right
}

DeleteBlock(block){
	block.lock = false;
	FreeBlock(block.blockId);
}

DeleteKey(){
}

DeleteKeyLeaf(block, key){
	offset = FindKeyInKey(block, key);
	if(offset == -1)
		throw DbKeyNotExist();
	LeftShiftLeaf(block, offset, 1);
	decrease the num of the block;
}

UpdateKey(block, oldKey, newKey){
	offset = FindKeyInNonleaf(block, oldKey);
	data[offset] = newKey;
	if(offset == 0 && !isRoot){
		UpdateKey(parent, oldKey, newKey);
	}
}