#include<stdio.h>
#include<malloc.h>
/*
疎妊笑逐(hash + sort)
室益胡闘 闘軒
offline
------------------------
online 熱戚澗 dynamic seg tree (煽澗 乞絹艦陥..)
*/
#define size 100003 // hash size
#define pnum 29 // 訊隔醸澗走 乞牽畏浦推;;;; 蒸嬢亀 企澗 line脊艦陥.
struct rain
{
	long long val;
};
struct node
{
	int idx;
	struct node* next;
};
struct query
{
	int qk;
	long long a, b;
};
struct query qlist[100010]; // query 煽舌遂
struct node* f[size], *r[size];
struct rain rtable[400010], sorted[400010]; // struct rain戚 焼観 long long生稽 馬偲亀 桔艦陥......
long long* tree; // seg tree
int tidx, n, qn, len;
long long alist[100010], origin[100010];
void input();
unsigned int get_k(long long);
int search(int, long long);
void push(int, int);
void save(long long);
void emq();
struct node pop(int);
void msort(struct rain[], int, int);
void merge(struct rain[], int, int, int);
int bs(struct rain[], int, long long);
void update(int, int);
void doquery(int, int, int, int, int, int);
void q1(long long, long long, int);
void q2(long long, long long, int);
void q3(long long, long long, int, int, int);
void q4(long long, int, int, int);
long long sum(int, int, int, int, int);
int kth(int, int, int, long long);
void make_answer();
int main(void)
{
	make_answer();
	return 0;
}
void make_answer()
{
	int i, len, node, start, end, l, r, g, idx;
	input(); // 脊径
	emq(); // 軒什闘級聖 搾趨掃艦陥.
	msort(rtable, 0, tidx - 1); //舛慶聖 背掃艦陥.
	/*
	rtable聖 舛慶背掃艦陥.
	rtable拭 煽舌鞠嬢責澗 呪級精 穿採 distinct杯艦陥. (set 坦軍 掻差 照器)
	益君蟹 貼事聖 察軒 馬奄是背辞 舛慶聖 背掃艦陥. (set坦軍 舛慶企惟)
	戚遭伊事聖 馬奄 是背辞 脊艦陥.
	*/
	for (len = tidx, node = start = l = r = 1; r - l + 1 < len; l <<= 1, r <<= 1, r |= 1); // seg tree size
	tree = (long long*)calloc(r + 1, sizeof(long long));//seg 拝雁
	for (g = l - 1, end = r - l + 1, i = 1; i <= n; i++)
	{
		//益軍 戚薦 offline生稽 庚薦研 祢艦猿 段奄脊径聖 seg tree拭 鋼慎聖 背掃艦陥.
		/*
		 rtable拭辞 origin[i](置段 i腰 走蝕税 竣食赤澗 旋竺勲)研 戚遭伊事背辞 idx研 閤焼 垣艦陥.
		 益君檎 薦亜 146 line拭辞 竺誤廃企稽 疎妊笑逐聖 梅走推?

		 origin[i]澗 idx稽 帖発戚 企壱
		 seg tree leaf node税 舛税昔 勧戚 origin[i]mm竣昔 亀獣税 姐呪澗
		 勧戚 idxmm 竣昔 亀獣税 姐呪稽 帖発戚 桔艦陥.
		*/
		idx = bs(rtable, tidx, origin[i]);
		//益掘辞 idx研 奄層生稽 seg tree研 update 杯艦陥.
		update(g + idx + 1, 1); // seg研 1base稽 梅嬢推.. rtable精 0base戚虞辞 + 1 背醤 杯艦陥.....
	}
	//戚薦 汀軒研 叔楳背 詐獣陥.
	doquery(node, start, end, l, r, g);
	free(tree);//背薦
	/*
	庚薦 陥 熱壱 窮 持唖

	瓜戚 hash研 紫遂拝 琶推亜 蒸柔艦陥
	乞窮 汽戚斗研 煽舌廃及 舛慶馬壱 戚遭伊事聖 馬檎
	牌雌 旭精 葵拭 企背辞澗 牌雌 旭精 idx研 匝依戚奄 凶庚脊艦陥.
	*/
}
void input()
{
	int i, k, s;
	/*
	馬馬;;; 薦亜 C研 紫遂馬陥左艦 set戚 蒸柔艦陥.
	益掘辞 娃舘廃 背縮聖 姥薄梅柔艦陥. -> 紫叔 蒸嬢亀 鞠澗 採歳脊艦陥(託板 竺誤)
	*/
	scanf("%d %d", &n, &qn); // 亀獣呪 汀軒呪
	for (i = 1, tidx = 0; i <= n; i++)
	{
		scanf("%lld", &alist[i]); // alist -> area_list稽 持唖馬獣檎 畷拝牛 杯艦陥.
		origin[i] = alist[i];//神覗虞昔生稽 庚薦研 熱 依戚奄 凶庚拭 origin壕伸拭 煽舌聖 酔識 背砧嬢醤 杯艦陥.
		k = get_k(alist[i]); // hash key研 閤柔艦陥.
		s = search(k, alist[i]); // key人 value研 紫遂背辞 薄仙 hash table拭 value亜 煽舌企嬢 赤澗走 焼観走 伊事杯艦陥.
		if (s == -1) // 幻鉦 hash table拭 value亜 蒸陥檎 煽舌聖 杯艦陥.
		{
			push(k, tidx); // chaining hash
			save(alist[i]); // 戚 敗呪税 舛税稽 亜左檎
		}
	}
	//戚薦 亀獣原陥 段奄 勧税 旋竺勲聖 煽舌聖 梅壱 
	//汀軒級聖 煽舌背 脚獣陥.
	for (i = 0; i < qn; i++)
	{
		scanf("%d", &qlist[i].qk); // 汀軒曽嫌
		if (qlist[i].qk == 4) // 4腰 汀軒虞檎?
		{
			//馬蟹 煽舌
			scanf("%lld", &qlist[i].a);
		}
		else // 1, 2, 3腰 汀軒澗 2鯵 煽舌
		{
			scanf("%lld %lld", &qlist[i].a, &qlist[i].b);
			if (qlist[i].qk == 1) // 1腰 汀軒虞檎?
			{
				//走蝕 qlist[i].a拭 勧戚 qlist[i].bmm竣昔陥. 脊艦陥.
				alist[qlist[i].a] += qlist[i].b; // area_list[qlist[i].a] += qlist[i].b; 鋼慎背掃艦陥.
				k = get_k(alist[qlist[i].a]);// 益君檎 area_list[qlist[i].a]税 葵拭企廃 key研 閤柔艦陥.
				s = search(k, alist[qlist[i].a]); // hash table 貼事
				if (s == -1) // 蒸生檎
				{
					//煽舌
					/*
					PPT研 溌昔背 爽室推 ばば
					越稽 承形艦 琶径戚 格巷 蒸革推 ばばばばば
					*/
					push(k, tidx);
					save(alist[qlist[i].a]);
				}
				/*
				訊 戚係惟 馬蟹檎 3腰 4腰 汀軒 ��庚脊艦陥.

				室益胡闘 闘軒税 軒覗葛球税 舛税研 戚係惟 杯獣陥.
				-> kmm税 勧戚 竣戚 亀獣税 姐呪

				益君蟹 mm税 骨是亜 0 ~ 1000000000000000000(10 ^ 18) 戚虞辞 室益胡闘 闘軒 姥失聖 公杯艦陥.
				益君檎 酔軒澗 疎妊笑逐聖 背醤杯艦陥.

				坦製 脊径生稽 級嬢神澗 n鯵税 悪呪勲
				+
				汀軒稽 幻級嬢走澗 悪呪勲 = 汀軒姐呪 * 2
				=
				n + qn * 2 = 300000 (置焦析凶)  -> 軒覗葛球税 鯵呪

				戚澗 中歳備 室益胡闘 闘軒研 姥失拝呪 赤柔艦陥.

				*/
			}
			else if (qlist[i].qk == 2)
			{
				//走蝕 qlist[i].a拭 勧戚 qlist[i].bmm褐澗陥. 脊艦陥.
				alist[qlist[i].a] -= qlist[i].b;
				k = get_k(alist[qlist[i].a]);
				s = search(k, alist[qlist[i].a]);
				if (s == -1)
				{
					push(k, tidx);
					save(alist[qlist[i].a]);
				}
			}
			else
			{
				// 3腰汀軒 
				//薄仙 旋竺勲戚 qlist[i].a mm戚雌 qlist[i].b mm戚馬昔 姥蝕税 呪研 湿陥.
				k = get_k(qlist[i].a);
				s = search(k, qlist[i].a);
				if (s == -1)
				{
					push(k, tidx);
					save(qlist[i].a);
				}
				k = get_k(qlist[i].b);
				s = search(k, qlist[i].b);
				if (s == -1)
				{
					push(k, tidx);
					save(qlist[i].b);
				}
				//原濁亜走稽 hash table聖 貼事廃 板 煽舌杯艦陥.
			}
		}
	}
}
unsigned int get_k(long long val)
{
	//益撹 hash_size稽 蟹刊 蟹袴走研 key葵生稽 梅柔艦陥.
	return val % size;
	//hash 煽維雁廃陥檎... 益凶 hash func 陥獣 郊蝦惟推.....
}
int search(int k, long long val)
{
	//chaining 生稽 hash 姥失聖 梅奄拭 key葵聖 魚虞 疑析廃 葵戚 rtable拭 煽舌戚 企醸澗走 溌昔杯艦陥.
	struct node* temp;
	for (temp = f[k]; temp; temp = temp->next)
	{
		if (rtable[temp->idx].val == val)
		{
			return temp->idx;
		}
	}
	return -1;
}
void push(int k, int idx)
{
	//key人 rtable税 index
	//list push_back 紫叔 泥虞壱 左獣檎 桔艦陥.
	struct node* temp;
	temp = (struct node*)malloc(sizeof(struct node));
	temp->idx = idx;
	temp->next = 0;
	if (!f[k])
	{
		f[k] = temp;
	}
	else
	{
		r[k]->next = temp;
	}
	r[k] = temp;
}
void save(long long val)
{
	//rtable戚虞澗 壕伸拭 益撹 煽舌馬澗 娃舘廃 敗呪脊艦陥.
	//食奄拭澗 set坦軍 掻差企走 省澗 収切幻 煽舌戚 桔艦陥.
	//戚政澗 hash table拭辞 戚耕 煽舌企走 省精 value幻 煽舌馬奄 凶庚戚倉
	rtable[tidx++].val = val;
}
void emq()
{
	//list 搾酔奄
	int i;
	for (i = 0; i < size; i++)
	{
		while (f[i])
		{
			pop(i);
		}
	}
}
struct node pop(int k)
{
	//list front pop 紫叔 泥虞壱 左偲亀 巷号杯艦陥.
	struct node* temp, ret;
	temp = f[k];
	ret = *f[k];
	f[k] = f[k]->next;
	free(temp);
	return ret;
}
//merge sort脊艦陥. 持繰
void msort(struct rain list[], int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) >> 1;
		msort(list, left, mid);
		msort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}
//merge 脊艦陥. 持繰
void merge(struct rain list[], int left, int mid, int right)
{
	int i, j, k, l;
	k = i = left;
	j = mid + 1;
	while (i <= mid && j <= right)
	{
		if (list[i].val < list[j].val)
		{
			sorted[k++] = list[i++];
		}
		else
		{
			sorted[k++] = list[j++];
		}
	}
	if (mid < i)
	{
		for (l = j; l <= right; l++)
		{
			sorted[k++] = list[l];
		}
	}
	else
	{
		for (l = i; l <= mid; l++)
		{
			sorted[k++] = list[l];
		}
	}
	for (l = left; l <= right; l++)
	{
		list[l] = sorted[l];
	}
}
//戚遭 伊事. 持繰
int bs(struct rain list[], int limit, long long val)
{
	int left, mid, right;
	left = 0;
	right = limit - 1;
	while (left <= right)
	{
		mid = (left + right) >> 1;
		if (list[mid].val == val)
		{
			return mid;
		}
		if (list[mid].val < val)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
}
//seg update脊艦陥.
void update(int idx, int val)
{
	while (idx)
	{
		tree[idx] += val;
		idx >>= 1;
	}
}
void doquery(int node, int start, int end, int l, int r, int g)
{
	int i;
	for (i = 0; i < qn; i++)
	{
		switch (qlist[i].qk)
		{
		case 1: //1腰汀軒
			q1(qlist[i].a, qlist[i].b, g);
			break;
		case 2: //2腰汀軒
			q2(qlist[i].a, qlist[i].b, g);
			break;
		case 3: //3腰汀軒
			q3(qlist[i].a, qlist[i].b, node, start, end);
			break;
		case 4: //4腰汀軒
			q4(qlist[i].a, node, start, end);
			break;
		}
	}
}void q1(long long a, long long b, int g) // a腰 走蝕税 勧戚 b幻鏑 竣昔陥.
{
	int idx;
	//origin[a]研 idx稽 帖発
	idx = bs(rtable, tidx, origin[a]);
	//seg tree研 idx拭 魚虞 update - > 勧戚 idx幻鏑 竣昔 亀獣税 姐呪亜 -1 喫
	update(g + idx + 1, -1);
	//a 走蝕拭 b幻鏑 勧戚 竣戚艦 +=b 尻至
	origin[a] += b;
	//origin[a]税 葵戚 郊餓醸生艦 陥獣 idx研 閤焼紳陥.
	idx = bs(rtable, tidx, origin[a]);
	//勧戚 idx幻鏑 竣昔 亀獣税 姐呪亜 +1 喫
	update(g + idx + 1, 1);
}
void q2(long long a, long long b, int g) // a腰 走蝕税 勧戚 b幻鏑 褐澗陥.
{
	int idx;
	// q1敗呪研 凧壱
	idx = bs(rtable, tidx, origin[a]);
	update(g + idx + 1, -1);
	origin[a] -= b; // 食奄幻 郊解艦陥!!!!!
	idx = bs(rtable, tidx, origin[a]);
	update(g + idx + 1, 1);
}
void q3(long long a, long long b, int node, int start, int end) // 勧戚 amm ~ bmm 幻鏑 竣昔 亀獣税 姐呪.
{
	int from_idx, to_idx;
	long long ans;
	//a 研 from_idx稽 帖発
	from_idx = bs(rtable, tidx, a);
	//b 研 to_idx稽 帖発
	to_idx = bs(rtable, tidx, b);
	//seg tree leaf node税 舛税亜 kmm竣昔 亀獣税 姐呪戚艦
	//seg tree拭辞 from_idx ~ to_idx紫戚税 杯聖 姥廃陥.
	ans = sum(node, start, end, from_idx + 1, to_idx + 1);
	printf("%lld\n", ans);
}
//seg sum敗呪
long long sum(int node, int start, int end, int left, int right)
{
	if (left > end || right < start)
	{
		return 0;
	}
	if (left <= start && end <= right)
	{
		return tree[node];
	}
	return sum(node << 1, start, (start + end) >> 1, left, right) + sum((node << 1) | 1, ((start + end) >> 1) + 1, end, left, right);
}
void q4(long long a, int node, int start, int end) //薄仙 旋竺勲戚 a腰属稽 弦精 亀獣拭 竣昔 勧戚 護 mm昔走 湿陥.
{
	int idx;
	//旋竺勲戚 k腰属稽 弦精 亀獣税 旋竺勲聖 呪馬澗 汀軒
	/*
	k腰属稽 弦精 -> n - k 腰属昔 亀獣税 旋竺勲!!!
	益君檎 酔軒澗 'n - k 腰属昔 亀獣税 旋竺勲'聖 蟹展鎧澗 seg tree leaf node税 idx研 姥馬檎 桔艦陥.
	*/
	idx = kth(node, start, end, n - a + 1);
	/*
	益軍 idx研 姥梅生檎 陥獣 帖発背醤 杯艦陥.
	走榎億 kmm税 旋竺勲聖 leaf node税 昔畿什稽 帖発梅生艦

	走榎精 leaf node税 idx研 kmm税 旋竺勲生稽 帖発背 窒径馬檎 桔艦陥.
	*/
	printf("%lld\n", rtable[idx - 1].val); // 戚係惟推.
}
//segment tree kth func
int kth(int node, int start, int end, long long val)
{
	if (start == end) // idx研 達製
	{
		return end;
	}
	//鋼鋼梢 蟹刊嬢辞 持唖馬檎
	if (tree[node << 1] >= val) // 坦製採斗 掻娃 猿走 (図楕 鋼) 税 杯戚 val 左陥 滴檎 陥獣 図畷聖 坐醤杯艦陥.. 坪球左舘 益顕聖 益形左獣檎 戚背亜 襲柔艦陥.........
	{
		return kth(node << 1, start, (start + end) >> 1, val);
	}
	return kth((node << 1) | 1, ((start + end) >> 1) + 1, end, val - tree[node << 1]);  // 掻娃 陥製採斗 魁 猿走 (神献楕 鋼)
}