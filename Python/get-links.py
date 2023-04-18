'''
Created on Dec 30, 2021

@author: jonesy
'''

from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from pymongo import MongoClient
import time


client = MongoClient()

options = webdriver.ChromeOptions()
options.add_argument("--ignore-certificate-errors")
options.add_argument("--incognito")


#journal_url = "https://www.sciencedirect.com/"
driver = webdriver.Chrome(options=options)

# filter_list = ["Skip to main content", "Sign in", "Register", "Journals & Books", "Help", "About ScienceDirect", "Remote access",
               # "Shopping cart", "Advertise", "Contact and support", "Terms and conditions", "Privacy policy", "use of cookies",
               # "Order journal", "Submit your article", "Guide for authors", "Articles & Issues", "About", "Publish", "issue"]


source_name = "Democracy Digest"
page_url = "https://www.demdigest.org/"
#page_url = "https://www.thebulwark.com/bulwark-originals/"
driver.get(page_url)
soup = BeautifulSoup(driver.page_source, "lxml")
#volume_links = soup.find_all("a", rel = "bookmark")
#next_page = soup.find("a", class_ = "next")
volume_link_list = []
year_volume_list = []

for i in range(9):
  driver.get(page_url)
  soup = BeautifulSoup(driver.page_source, "lxml")
  volume_links = soup.find_all("a", rel = "bookmark")
  next_page = soup.find("a", class_ = "next")
  
  if len(volume_links) > 1:
    for volume_link in volume_links:
      #if volume_link.text not in filter_list: 
        #temp_url = journal_url + volume_link["href"]
        temp_url = volume_link["href"]
        print(temp_url)
        #print(volume_link["href"])
        #print("\n")
  else:
    print(len(volume_links))
    print("\n")
    print("no issues")
    
  print(next_page["href"])
  page_url = next_page["href"]
  driver.find_element(By.PARTIAL_LINK_TEXT, "Next ").click()
  #time.sleep(1)
  
  
print(len(volume_links))
