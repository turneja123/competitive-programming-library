//https://www.codechef.com/problems/RGBGRID
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 6;
const int M = 50;
const int MAX = 730;

int pw[N];
bool cant[MAX][MAX][MAX];
bool skip[MAX];
long long dp[MAX][MAX][M];
vector<int> a[MAX];

typedef long long ll;

const int base = 1000000000;
const int base_digits = 9;

struct bigint {
	vector<int> a;
	int sign;
	int size(){
		if(a.empty())return 0;
		int ans=(a.size()-1)*base_digits;
		int ca=a.back();
		while(ca)
			ans++,ca/=10;
		return ans;
	}
	bigint operator ^(const bigint &v){
		bigint ans=1,a=*this,b=v;
		while(!b.isZero()){
			if(b%2)
				ans*=a;
			a*=a,b/=2;
		}
		return ans;
	}
	string to_string(){
		stringstream ss;
		ss << *this;
		string s;
		ss >> s;
		return s;
	}
	int sumof(){
		string s = to_string();
		int ans = 0;
		for(auto c : s)  ans += c - '0';
		return ans;
	}

	bigint() :
		sign(1) {
	}

	bigint(long long v) {
		*this = v;
	}

	bigint(const string &s) {
		read(s);
	}

	void operator=(const bigint &v) {
		sign = v.sign;
		a = v.a;
	}

	void operator=(long long v) {
		sign = 1;
		a.clear();
		if (v < 0)
			sign = -1, v = -v;
		for (; v > 0; v = v / base)
			a.push_back(v % base);
	}

	bigint operator+(const bigint &v) const {
		if (sign == v.sign) {
			bigint res = v;

			for (int i = 0, carry = 0; i < (int) max(a.size(), v.a.size()) || carry; ++i) {
				if (i == (int) res.a.size())
					res.a.push_back(0);
				res.a[i] += carry + (i < (int) a.size() ? a[i] : 0);
				carry = res.a[i] >= base;
				if (carry)
					res.a[i] -= base;
			}
			return res;
		}
		return *this - (-v);
	}

	bigint operator-(const bigint &v) const {
		if (sign == v.sign) {
			if (abs() >= v.abs()) {
				bigint res = *this;
				for (int i = 0, carry = 0; i < (int) v.a.size() || carry; ++i) {
					res.a[i] -= carry + (i < (int) v.a.size() ? v.a[i] : 0);
					carry = res.a[i] < 0;
					if (carry)
						res.a[i] += base;
				}
				res.trim();
				return res;
			}
			return -(v - *this);
		}
		return *this + (-v);
	}

	void operator*=(int v) {
		if (v < 0)
			sign = -sign, v = -v;
		for (int i = 0, carry = 0; i < (int) a.size() || carry; ++i) {
			if (i == (int) a.size())
				a.push_back(0);
			long long cur = a[i] * (long long) v + carry;
			carry = (int) (cur / base);
			a[i] = (int) (cur % base);
			//asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
		}
		trim();
	}

	bigint operator*(int v) const {
		bigint res = *this;
		res *= v;
		return res;
	}

	void operator*=(long long v) {
		if (v < 0)
			sign = -sign, v = -v;
		if(v > base){
			*this = *this * (v / base) * base + *this * (v % base);
			return ;
		}
		for (int i = 0, carry = 0; i < (int) a.size() || carry; ++i) {
			if (i == (int) a.size())
				a.push_back(0);
			long long cur = a[i] * (long long) v + carry;
			carry = (int) (cur / base);
			a[i] = (int) (cur % base);
			//asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
		}
		trim();
	}

	bigint operator*(long long v) const {
		bigint res = *this;
		res *= v;
		return res;
	}

	friend pair<bigint, bigint> divmod(const bigint &a1, const bigint &b1) {
		int norm = base / (b1.a.back() + 1);
		bigint a = a1.abs() * norm;
		bigint b = b1.abs() * norm;
		bigint q, r;
		q.a.resize(a.a.size());

		for (int i = a.a.size() - 1; i >= 0; i--) {
			r *= base;
			r += a.a[i];
			int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
			int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
			int d = ((long long) base * s1 + s2) / b.a.back();
			r -= b * d;
			while (r < 0)
				r += b, --d;
			q.a[i] = d;
		}

		q.sign = a1.sign * b1.sign;
		r.sign = a1.sign;
		q.trim();
		r.trim();
		return make_pair(q, r / norm);
	}

	bigint operator/(const bigint &v) const {
		return divmod(*this, v).first;
	}

	bigint operator%(const bigint &v) const {
		return divmod(*this, v).second;
	}

	void operator/=(int v) {
		if (v < 0)
			sign = -sign, v = -v;
		for (int i = (int) a.size() - 1, rem = 0; i >= 0; --i) {
			long long cur = a[i] + rem * (long long) base;
			a[i] = (int) (cur / v);
			rem = (int) (cur % v);
		}
		trim();
	}

	bigint operator/(int v) const {
		bigint res = *this;
		res /= v;
		return res;
	}

	int operator%(int v) const {
		if (v < 0)
			v = -v;
		int m = 0;
		for (int i = a.size() - 1; i >= 0; --i)
			m = (a[i] + m * (long long) base) % v;
		return m * sign;
	}

	void operator+=(const bigint &v) {
		*this = *this + v;
	}
	void operator-=(const bigint &v) {
		*this = *this - v;
	}
	void operator*=(const bigint &v) {
		*this = *this * v;
	}
	void operator/=(const bigint &v) {
		*this = *this / v;
	}

	bool operator<(const bigint &v) const {
		if (sign != v.sign)
			return sign < v.sign;
		if (a.size() != v.a.size())
			return a.size() * sign < v.a.size() * v.sign;
		for (int i = a.size() - 1; i >= 0; i--)
			if (a[i] != v.a[i])
				return a[i] * sign < v.a[i] * sign;
		return false;
	}

	bool operator>(const bigint &v) const {
		return v < *this;
	}
	bool operator<=(const bigint &v) const {
		return !(v < *this);
	}
	bool operator>=(const bigint &v) const {
		return !(*this < v);
	}
	bool operator==(const bigint &v) const {
		return !(*this < v) && !(v < *this);
	}
	bool operator!=(const bigint &v) const {
		return *this < v || v < *this;
	}

	void trim() {
		while (!a.empty() && !a.back())
			a.pop_back();
		if (a.empty())
			sign = 1;
	}

	bool isZero() const {
		return a.empty() || (a.size() == 1 && !a[0]);
	}

	bigint operator-() const {
		bigint res = *this;
		res.sign = -sign;
		return res;
	}

	bigint abs() const {
		bigint res = *this;
		res.sign *= res.sign;
		return res;
	}

	long long longValue() const {
		long long res = 0;
		for (int i = a.size() - 1; i >= 0; i--)
			res = res * base + a[i];
		return res * sign;
	}

	friend bigint gcd(const bigint &a, const bigint &b) {
		return b.isZero() ? a : gcd(b, a % b);
	}
	friend bigint lcm(const bigint &a, const bigint &b) {
		return a / gcd(a, b) * b;
	}

	void read(const string &s) {
		sign = 1;
		a.clear();
		int pos = 0;
		while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
			if (s[pos] == '-')
				sign = -sign;
			++pos;
		}
		for (int i = s.size() - 1; i >= pos; i -= base_digits) {
			int x = 0;
			for (int j = max(pos, i - base_digits + 1); j <= i; j++)
				x = x * 10 + s[j] - '0';
			a.push_back(x);
		}
		trim();
	}

	friend istream& operator>>(istream &stream, bigint &v) {
		string s;
		stream >> s;
		v.read(s);
		return stream;
	}

	friend ostream& operator<<(ostream &stream, const bigint &v) {
		if (v.sign == -1)
			stream << '-';
		stream << (v.a.empty() ? 0 : v.a.back());
		for (int i = (int) v.a.size() - 2; i >= 0; --i)
			stream << setw(base_digits) << setfill('0') << v.a[i];
		return stream;
	}

	static vector<int> convert_base(const vector<int> &a, int old_digits, int new_digits) {
		vector<long long> p(max(old_digits, new_digits) + 1);
		p[0] = 1;
		for (int i = 1; i < (int) p.size(); i++)
			p[i] = p[i - 1] * 10;
		vector<int> res;
		long long cur = 0;
		int cur_digits = 0;
		for (int i = 0; i < (int) a.size(); i++) {
			cur += a[i] * p[cur_digits];
			cur_digits += old_digits;
			while (cur_digits >= new_digits) {
				res.push_back(int(cur % p[new_digits]));
				cur /= p[new_digits];
				cur_digits -= new_digits;
			}
		}
		res.push_back((int) cur);
		while (!res.empty() && !res.back())
			res.pop_back();
		return res;
	}

	typedef vector<long long> vll;

	static vll karatsubaMultiply(const vll &a, const vll &b) {
		int n = a.size();
		vll res(n + n);
		if (n <= 32) {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					res[i + j] += a[i] * b[j];
			return res;
		}

		int k = n >> 1;
		vll a1(a.begin(), a.begin() + k);
		vll a2(a.begin() + k, a.end());
		vll b1(b.begin(), b.begin() + k);
		vll b2(b.begin() + k, b.end());

		vll a1b1 = karatsubaMultiply(a1, b1);
		vll a2b2 = karatsubaMultiply(a2, b2);

		for (int i = 0; i < k; i++)
			a2[i] += a1[i];
		for (int i = 0; i < k; i++)
			b2[i] += b1[i];

		vll r = karatsubaMultiply(a2, b2);
		for (int i = 0; i < (int) a1b1.size(); i++)
			r[i] -= a1b1[i];
		for (int i = 0; i < (int) a2b2.size(); i++)
			r[i] -= a2b2[i];

		for (int i = 0; i < (int) r.size(); i++)
			res[i + k] += r[i];
		for (int i = 0; i < (int) a1b1.size(); i++)
			res[i] += a1b1[i];
		for (int i = 0; i < (int) a2b2.size(); i++)
			res[i + n] += a2b2[i];
		return res;
	}

	bigint operator*(const bigint &v) const {
		vector<int> a6 = convert_base(this->a, base_digits, 6);
		vector<int> b6 = convert_base(v.a, base_digits, 6);
		vll a(a6.begin(), a6.end());
		vll b(b6.begin(), b6.end());
		while (a.size() < b.size())
			a.push_back(0);
		while (b.size() < a.size())
			b.push_back(0);
		while (a.size() & (a.size() - 1))
			a.push_back(0), b.push_back(0);
		vll c = karatsubaMultiply(a, b);
		bigint res;
		res.sign = sign * v.sign;
		for (int i = 0, carry = 0; i < (int) c.size(); i++) {
			long long cur = c[i] + carry;
			res.a.push_back((int) (cur % 1000000));
			carry = (int) (cur / 1000000);
		}
		res.a = convert_base(res.a, 6, base_digits);
		res.trim();
		return res;
	}
};

vector<string> hard_c_5{"52", "22568", "9550778", "2880302852", "769471580012", "195869098764776", "48741329461378582", "11991605952561005392", "2932939814410560913776", "715147129474875055832352", "174095153515423453382915094", "42345588261059954362477881612", "10295186238560088820566740023444", "2502400604345114372098007723859744", "608169626009613212962199025950802934", "147796323932067358664521338078691657824", "35915935992882770595791321116847775967752", "8727756405612332966903470273447414452061472", "2120868483590849401086854074331285487728579450", "515374088933840870436467490195818351483773949588", "125236295838222080760668167843113069517643903661120", "30432470371453731536013856557481348114694965012705640", "7395096797795803583218964366666298547609655558587311066", "1797009358148378511777027756240185066271218654741366458808", "436673381666442664311901656693029591348973238513302995060840", "106111645598602654225161320108909132991287869519514506925510752", "25785131663536044109799167585301732374531233181654067740568253794", "6265787223735237455859527976672700157262451138993838292784756144068", "1522586324905616270395579400747693172862848801511159899845341929130912", "369988480753833768671043976295986168932778531384349070956090581331271456", "89907201312499445953935618703411627124759507368269978309673539262945243766", "21847449981916454249664707521619357386600645229803790288581171316533629673192", "5308930353711606875934013431904627777968940133155689735165078019497444788889756", "1290070076995215216246057324310562377509261103565739150454518439825302149059103472", "313487028844117610071827397328315637680286979820937080041488520467644798421509708662", "76177348026403521015498299257130556789060888227026705215637862531843619001064462027604", "18511095572640507356564795906349094708390285061764079795461666747652047298714591771052744", "4498196224437947879397768660825273488284869394375320577073745883268700369626814845600649544", "1093061682575271007547203161770102974862814813114541396461971501838571322853796883279124878158", "265613988870533700141135623338724673213874226003207695289042483821100385288044514219741715391464", "64544199296150130960933102200947770247362924617012978144799367785822011306208752076602036000590468", "15684240429043050530595952554773474645514636755320838413317807889309102845001234711636116120291405784", "3811270424267573694998565670483471429461637034766154673188504761154145449582914184972330481079259385610", "926138713098321956076481360505081149369389116346765431215373075573883040144218427073442450166385727261100", "225051707283059754906967784136097837249041738303140792372511744214884269460018490103300344435890155303388612", "54687564869805081541696132593030230103458176453489727033319118139621147996332557053113478470522720625216762720", "13289078263365409899204899761701815021156620602488526529676181556001703557536577711495460554116260238068055731874", "3229246017998151780912257996470191706576215887794752649056240878028309956575967329972747217333787008519202380282672", "784706782373596854070634091459957002208583165318079554137996313195946411265388396328306455295667283266929373232370852", "190683748116789952411419908808826001262897173731573429402354621085972285836102593729772068211553477418480561326761139024"};
vector<string> hard_c_6{"200", "251600", "292714936","251899621024","195869098764776","146789354948245152","108329424460870308280","79407384780752285291744","58031412799542147532769664","42352165059574660059953704416","30890304313825101879097939843632","22524164855273436429328658394120688","16421807743185793600926876403540052728","11972055292838787460606607814819080042000","8727812013261675471982503542080244721693520","6362635496846801977258678249496364521412488912","4638381227646598046737674485024770852508605417808","3381386489544128067320163849964239246763873002097776","2465032917507530174173629897704409824084135727944349112","1797009710867228030081766437145990398027624391486198469488","1310020314519461372248452243506267873354284660299475301844064","955004886825959332809603397425254398349952832708875138333391088","696198588049541605880929935696273457564748967691813553473252137960","507528779109142678581010104842339933912714544927383789182740909683824","369988482745680860123574292452797201267578193436232333820178137203851544","269721604836129718190410543390769682017338093687679773814016859492378135024","196627050226917745696358857968312436598632150520741225115837998606298645746832","143341119714741345028482775417055905329874768147918824927662446145218188367445632","104495676304776393369277777606190107183893664162126934499149616654581718736955720376","76177348036968016326097341723113549013913253930472939397611577610920613885783554673728","55533286722504175652290936044470121187826189352742593567671820903732185823944287004682496","40483766021876912645438006898318834251957066937318554060906224849499336119221813697378224944","29512665430334289172119829412420773348274216323717423587425856859559948133125934140696564023456","21514733098840908111282746978655200984108600921413966387357244248212589421707221893049075602604144","15684240429096943991800746647075166955875049087406907444209251895766989945776410845251300967338077016","11433811272825487391073581045380979387708417905730825221775386821613160209451984688227834400915950039904","8335248417894333059148603023937638901217810351646541080531026916987540678920918980168277705333841887407336","6076396096646469141091169455323513046092717503660772567399133084745096587351840752202560831106632061984796208","4429692754455770435245210348905473247936272094675972530362997435933595599349286174943764609505557257846634270680","3229246017998419585188381392039572186299783560173639630020873076442564051937851808305277659213918234525793086976768","2354120347120901573136340795214828724859499575927997875691433236251320330355654802450954765022389043637163180142229088","1716153733051154941965696847726883833988106633677313398119331051592481201402545923554667502013701791323632016436764740912","1251076071394297784058946873380632857371340970068107964926752009270291478883856093993489383438103024800636435095692501081440","912034456046445006282389573845561797569279487173815382915074516100845549277854482262667386479358127475168477340865689412308128","664873118457859042869566896502289272838279393344915031539577813017663026639077572294563438974269750673527642919499167517128540864","484692503355779450950013421461484832779800711498419524845846980602961921182314668451532391826542498175579386762022420151594884260048","353340834946363288518186884528182065711552337367548304377911159044850070984578684137600987010374349893371078397797012045013111951884512","257585468675898859994492140152792506951145654466929375673985805459817175306669282072321318513894149891157739307575091738130387522878950848","187779806664730276405057528594328215776035069497086665792758671536238907011651131472782502913793768418428722818041669137855943993749803640216","136891479058588373960690108286639901487557499984079527091221347402617246170720508593714473103494433924548338247379708533819950558279573178333568"};

int main() {
    IOS;
    int n, m; long long MOD;
    cin >> n >> m >> MOD;
    if (n == 5) {
        bigint ans = hard_c_5[m - 1];
        cout << ans % MOD;
        return 0;
    }
    if (n == 6) {
        bigint ans = hard_c_6[m - 1];
        cout << ans % MOD;
        return 0;
    }
    pw[0] = 3;
    for (int i = 1; i < n; i++) {
        pw[i] = pw[i - 1] * 3;
    }
    int ct = 0;
    for (int i = 0; i < pw[n - 1]; i++) {
        int k = i;
        for (int j = 0; j < n; j++) {
            a[i].push_back(k % 3);
            k /= 3;
        }
        for (int j = 0; j < n - 2; j++) {
            if (a[i][j] == 0 && a[i][j + 1] == 1 && a[i][j + 2] == 2) {
                skip[i] = true;
            }
        }
        for (int j = 2; j < n; j++) {
            if (a[i][j] == 0 && a[i][j - 1] == 1 && a[i][j - 2] == 2) {
                skip[i] = true;
            }
        }
        if (!skip[i]) {
            ct++;
        }
    }
    if (m == 1) {
        cout << pw[n - 1] - ct;
        return 0;
    }
    for (int i = 0; i < pw[n - 1]; i++) {
        for (int j = 0; j < pw[n - 1]; j++) {
            if (skip[i] || skip[j]) {
                continue;
            }
            dp[i][j][1] = 1;
            for (int last = 0; last < pw[n - 1]; last++) {
                if (skip[last]) {
                    continue;
                }
                for (int k = 0; k < n; k++) {
                    if (a[i][k] == 0 && a[j][k] == 1 && a[last][k] == 2) {
                        cant[i][j][last] = true;
                    }
                    if (a[i][k] == 2 && a[j][k] == 1 && a[last][k] == 0) {
                        cant[i][j][last] = true;
                    }
                }
            }
        }
    }
    long long tot = pw[n - 1] * pw[n - 1] % MOD;
    for (int i = 2; i < m; i++) {
        tot = tot * pw[n - 1] % MOD;
        for (int j = 0; j < pw[n - 1]; j++) {
            if (skip[j]) {
                continue;
            }
            for (int last = 0; last < pw[n - 1]; last++) {
                for (int prv = 0; prv < pw[n - 1]; prv++) {
                    if (cant[prv][last][j]) {
                        continue;
                    }
                    dp[last][j][i] = (dp[last][j][i] + dp[prv][last][i - 1]) % MOD;
                }
            }
        }
    }
    for (int j = 0; j < pw[n - 1]; j++) {
        for (int last = 0; last < pw[n - 1]; last++) {
            tot = (tot - dp[last][j][m - 1] + MOD) % MOD;
        }
    }
    cout << tot;
    return 0;
}
