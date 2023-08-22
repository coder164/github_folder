#include "list_functions.h"
#include "listinternal.h"

typedef int (*InnerFunc)(int _res, void* _innerContext);
typedef int (*GenericFunc)(void* _element, void* _context);

typedef struct Helper
{
    GenericFunc m_func;
    void* m_context;
    InnerFunc m_innerFunc;
    ListItr m_other;
} Helper;

/* functions declarations */
static int InnerFind(int _res, void* _innerContext);
static int InnerCount(int _res, void* _innerContext);
static ListItr InnerForEach(ListItr _begin, ListItr _end,
    Helper _helper);

static int Continue(int _res, ListItr _innerContext);
/* func declarations */

ListItr ListItrFindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
    Helper helper;
    if (NULL == _begin || NULL == _end || NULL == _predicate ||
        NULL == _context)
    {
        return NULL;
    }
    helper.m_func = _predicate;
    helper.m_context = _context;
    helper.m_other = NULL;
    helper.m_innerFunc = InnerFind;
    return InnerForEach(_begin, _end, helper);
}

size_t ListItrCountIf(ListItr _begin, ListItr _end,
    PredicateFunction _predicate, void* _context)
{
    size_t count = 0;
    Helper helper;
    if (NULL == _begin || NULL == _end || NULL == _predicate)
    {
        return 0;
    }
    helper.m_func = _predicate;
    helper.m_context = _context;
    helper.m_other = &count;
    helper.m_innerFunc = InnerCount;
    InnerForEach(_begin, _end, helper);
    return count;
}

ListItr ListItrForEach(ListItr _begin, ListItr _end,
    ListActionFunction _action, void* _context)
{
    Helper helper;
    if (NULL == _begin || NULL == _end || NULL == _action)
    {
        return _begin;
    }
    helper.m_context = _context;
    helper.m_func = _action;
    helper.m_other = NULL;
    helper.m_innerFunc = Continue;
    return InnerForEach(_begin, _end, helper);
}

/************************* assistant funcs **********************/

int InnerFind(int _res, ListItr _innerContext)
{
    return (_res == 0) ? (0) : (1);
}

int InnerCount(int _res, ListItr _innerContext)
{
    if(_res != 0)
    {
        (*(int*)_innerContext)++;
    }
    return 1;
}

static int Continue(int _res, ListItr _innerContext)
{
    return (_res == 0) ? (0) : (1);
}

ListItr InnerForEach(ListItr _begin, ListItr _end, Helper _helper)
{
    int res;
    void* currentData;
    ListItr currentItr = _begin;
    while (currentItr != _end)
    {
        currentData = ListItrGet(currentItr);
        res = _helper.m_func(currentData, _helper.m_context);
        if (0 == _helper.m_innerFunc(res, _helper.m_other))
        {
            break;
        }
        else
        {
            currentItr = ((Node*)currentItr) -> m_next;
        }
    }
    return currentItr;
}

