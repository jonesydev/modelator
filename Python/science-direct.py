'''
Created on Dec 19, 2021

@author: jonesy

Get journal and book titles.
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

#Domain isn't necessary for computation, just a data member for the database to be used for later analysis.
domain = "chemical_engineering"
#Subdomain is necessary.
subdomain = "bioengineering"
#subdomain = "applied-catalysis"

#URL for list of journals in a subdomain.
main_url = "https://www.sciencedirect.com/browse/journals-and-books?contentType=JL&subject=" + subdomain
#URL prefix for a particular journal. 
journal_url = "https://www.sciencedirect.com/journal/"

driver = webdriver.Chrome(options=options)
journal_driver = webdriver.Chrome(options=options)

driver.get(main_url)



#driver.execute_script("arguments[0].click();", previews_checkbox)

#time.sleep(1)

soup = BeautifulSoup(driver.page_source, "lxml")

filter_list = ["Skip to main content", "Sign in", "Register", "Journals & Books", "Help", "About ScienceDirect", "Remote access",
               "Shopping cart", "Advertise", "Contact and support", "Terms and conditions", "Privacy policy", "use of cookies",
               "Order journal", "Submit your article", "Guide for authors", "Articles & Issues", "About", "Publish"]
title_links = soup.find_all("span", class_="anchor-text")
url_list = []
url_slugs = []

#Create the URL slugs to append to the URL prefix for each journal's list of issues.
for title_link in title_links:  
  if title_link.text not in filter_list and len(title_link.text) > 0:
    slug = title_link.text.lower().replace(":", "").replace(" ", "-") + "/issues"
    url_slugs.append(slug)
    #print(slug)
    #print("\n")
   
#Create a list of URLs that each link to a journal's list of issues.
for url in url_slugs:
  temp_url = journal_url + url
  url_list.append(temp_url)
  #print(temp_url)
  #print("\n")

#Visit each journal's list of issues and get the year and volume number.
for url in url_list:
  journal_driver.get(url)
  #Each year's volumes are listed inside an accordion link. This opens those links
  #to expose the listing for each individual volume for that year.
  for i in range(17):
    button_id = "0-accordion-tab-" + str(i)
    volume_button = journal_driver.find_element(By.ID, button_id)
    journal_driver.execute_script("arguments[0].click();", volume_button)        
    time.sleep(1)
  ##journal_soup = BeautifulSoup(journal_driver.page_source, "lxml") 
  #volume_links = journal_soup.find_all("button", class_="accordion-panel-title")  
  time.sleep(1)
  volume_links = soup.find_all("span", class_="anchor-text")
  
  
  for volume_link in volume_links:
    if volume_link.text not in filter_list:
      #volume_link["aria-expanded"]="true"
      print(volume_link.text)
      print("\n")
  
  