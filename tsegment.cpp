#include "tsegment.h"
#include "tdata.h"
#include <iostream>

TSegment::TSegment(TData* ds, size_t f, size_t t) : dset(ds), index_from(f), index_to(t)
{
    std::cout << "TSegment Constructor" << std::endl;
}

TSegment::~TSegment()
{
    std::cout << " TSegment ~Destructor" << std::endl;
}

void TSegment::display_ages_vector()
{
    std::cout << "Data in the ages vector: " << std::endl;
    for (int i = 0; i < get_ages_vector_size(); i++)
    {
        std::cout << i << ": " << this->ages[i] << std::endl;
    }
}

void TSegment::display_depths_vector()
{
    std::cout << "Data in the depths vector: " << std::endl;
    for (int i = 0; i < get_depths_vector_size(); i++)
    {
        std::cout << i << ": " << this->depths[i] << std::endl;
    }
}

void TSegment::display_lsr_values_vector()
{
    std::cout << "Data in the lsr_values vector: " << std::endl;
    for (int i = 0; i < get_lsr_values_vector_size(); i++)
    {
        std::cout << i << ": " << this->lsr_values[i] << std::endl;
    }
}

void TSegment::display_lsr_plot_values_vector()
{
    std::cout << "Data in the lsr_plot_values vector: " << std::endl;
    for (int i = 0; i < get_lsr_plot_values_vector_size(); i++)
    {
        std::cout << i << ": " << this->lsr_plot_values[i] << std::endl;
    }
}

void TSegment::display_lsr_plot_ages_vector()
{
    std::cout << "Data in the lsr_plot_ages vector: " << std::endl;
    for (int i = 0; i < get_lsr_plot_ages_vector_size(); i++)
    {
        std::cout << i << ": " << this->lsr_plot_ages[i] << std::endl;
    }
}

void TSegment::compute_lsr_values()
{
    for (int i = 1; i < this->ages.size(); i++)
    {
        this->lsr_values.push_back(((this->depths[i] - this->depths[i-1]) * 100) / ((this->ages[i] - this->ages[i-1]) * 1000));
    }

    for (int i = 0; i < this->ages.size() - 1; i++)
    {
        this->lsr_plot_values.push_back(this->lsr_values[i]);
        this->lsr_plot_values.push_back(this->lsr_values[i]);
        this->lsr_plot_ages.push_back(this->ages[i]);
        this->lsr_plot_ages.push_back(this->ages[i+1]);
    }
}

void TSegment::copy_ages_to_segment()
{
    for (int i = this->index_from; i < this->index_to; i ++)
    {
        this->set_ages(this->dset->get_ages(i));
    }
}

void TSegment::copy_depths_to_segment()
{
    for (int i = this->index_from; i < this->index_to; i ++)
    {
        this->set_depths(this->dset->get_depths(i));
    }
}

/* perform fitting */
void TSegment::perform_fitting()
{
    for (int i = 0; i < this->fit.size(); i++)
    {
        this->g1->Fit(this->fit[i]->f, "N");
        this->fit[i]->chi2 = this->fit[i]->f->GetChisquare();
        this->fit[i]->ndf = this->fit[i]->f->GetNDF();
        // std::cout << i << ": Chi2/ndf = " << this->fit[i]->chi2 / this->fit[i]->ndf << std::endl;
    }
}

/* find the best fit */
int TSegment::find_best_fit()
{
    int best_fit_index = -1;
    int current_index{};

    for (int i = 0; i < this->fit.size() - 1; i++)
    {
        if(std::isnan(this->fit[i]->chi2 / this->fit[i]->ndf) == true)
           continue;
        if((this->fit[i]->chi2 == 0) || (this->fit[i]->ndf == 0))
            continue;
        if((this->fit[i]->chi2 / this->fit[i]->ndf) < (this->fit[i+1]->chi2 / this->fit[i+1]->ndf))
        {   
            if (best_fit_index == -1) 
                best_fit_index = current_index = i;
            else
            {
                current_index = i;
                if ((this->fit[current_index]->chi2 / this->fit[current_index]->ndf) < (this->fit[best_fit_index]->chi2 / this->fit[best_fit_index]->ndf))
                    best_fit_index = current_index;
            }
        }
        // std::cout << i << ": Chi2/ndf = " << this->fit[i]->chi2 / this->fit[i]->ndf << std::endl;
    }

    for (int i = 0; i <= best_fit_index; i++)
    {
        this->fit[best_fit_index]->parameters.push_back(this->fit[best_fit_index]->f->GetParameter(i));
    }

    // std::cout << "Best fit for this segment = " << this->fit[best_fit_index]->chi2 / this->fit[best_fit_index]->ndf << std::endl;
    return best_fit_index;
}

double TSegment::compute_polynomial_expression(int deg, double current_value)
{
    double temporary_result{};
    double total = this->fit[deg]->parameters[0];
    for (int i = 1; i <= deg; i++)
    {
        temporary_result = this->fit[deg]->parameters[i] * pow(current_value, i);
        total += temporary_result;
    }
    return total;
}

void TSegment::get_fit_line_for_plot(int deg)
{
    for (int i = 0; i < this->ages.size(); i++)
    {
        this->fit_line.push_back(compute_polynomial_expression(deg, this->ages[i]));
    }
}

void TSegment::plot_to_png(std::string f)
{
    this->cnv->Divide(2,1);
    this->cnv->cd(1);

    this->g1->SetTitle("Age vs Depth, raw");
    this->g1->SetMarkerColor(4);
    this->g1->SetMarkerSize(1.25);
    this->g1->SetMarkerStyle(20);
    
    perform_fitting();
    get_fit_line_for_plot(find_best_fit());
    this->set_g2_ptr();

    this->g2->SetTitle("Polynomial fit");
    this->g2->SetLineColor(2);
    this->g2->SetLineWidth(2);

    this->multi->Add(g1, "p");
    this->multi->Add(g2, "l");
    this->multi->SetName("AvD");
    this->multi->SetTitle("Age vs depth plot with polynomial smoothing; Age (Ma);");
    this->multi->GetXaxis()->CenterTitle();
    this->multi->GetYaxis()->CenterTitle();
    this->multi->Draw("A RY");

    // this->g1->Fit(this->fit[find_best_fit()]->f, "L");
    // this->g1->Draw("A P");
    
    this->cnv->cd(2);
    this->g3->SetTitle("LSR variability, raw");
    this->g3->SetLineColor(4);
    this->g3->SetLineWidth(2);
    this->g3->Draw("AL");

    this->cnv->Print(f.c_str());
}

/* setter functions */
void TSegment::set_ages(double a)
{
    this->ages.push_back(a);
}

void TSegment::set_depths(double d)
{
    this->depths.push_back(d);
}

void TSegment::set_g1_ptr()
{
    this->g1 = new TGraph(this->ages.size(), &this->ages[0], &this->depths[0]);
}

void TSegment::set_g2_ptr()
{
    this->g2 = new TGraph(this->ages.size(), &this->ages[0], &this->fit_line[0]);
}

void TSegment::set_g3_ptr()
{
    this->g3 = new TGraph(this->lsr_plot_ages.size(), &this->lsr_plot_ages[0], &this->lsr_plot_values[0]);
}

void TSegment::add_to_fit_vector(int d)
{
    this->fit.push_back(new TPolynomial(d));
}

/* getter functions */
TData* TSegment::get_dataset_ptr()
{
    return this->dset;
}

size_t TSegment::get_index_from()
{
    return this->index_from;
}

size_t TSegment::get_index_to()
{
    return this->index_to;
}

double TSegment::get_ages(int i)
{
    return this->ages[i];
}

double TSegment::get_depths(int i)
{
    return this->depths[i];
}

size_t TSegment::get_ages_vector_size()
{
    return this->ages.size();
}

size_t TSegment::get_depths_vector_size()
{
    return this->depths.size();
}

size_t TSegment::get_lsr_values_vector_size()
{
    return this->lsr_values.size();
}

size_t TSegment::get_lsr_plot_values_vector_size()
{
    return this->lsr_plot_values.size();
}

size_t TSegment::get_lsr_plot_ages_vector_size()
{
    return this->lsr_plot_ages.size();
}