import pytest
import itt

def test_itt_resume_and_pause():
    itt.resume()
    pass
    itt.pause()

    
def test_itt_task():
    domain = itt.domain_create("test_domain")
    itt.task_begin(domain, "task1")
    r = sorted([1/(k+1) for k in range(1, 10000)])
    itt.task_end(domain)
    itt.task_begin(domain, "task2")
    s = sum(1/(k+1) for k in range(1, 10000))
    itt.task_end(domain)

    
def test_itt_pt_region():
    i = itt.pt_region_create("region1")
    itt.pt_region_begin(i)
    s1 = "s" * (10**5)
    itt.pt_region_end(i)


def test_itt_detach():
    itt.detach()





